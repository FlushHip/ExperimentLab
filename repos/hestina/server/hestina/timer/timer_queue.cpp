#include "timer_queue.h"

#include "log/logger.h"
#include "net/channel.h"
#include "net/eloop_thread_pool.h"
#include "timer/timer.h"

#include <sys/timerfd.h>

#include <chrono>
#include <cstddef>
#include <memory>

namespace hestina {

namespace {

void read_timerfd(int fd) {
    uint64_t value{};
    read(fd, &value, sizeof(value));
}

}  // namespace

// TODO (flushhip): thread safe, use eventloop single thread to operate

timer_queue::timer_queue()
    : loop_thread_(std::make_unique<event_loop_thread>())
    , fd_(::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC))
    , channel_(std::make_unique<channel>(loop_thread_->get_eloop(), fd_)) {
    loop_thread_->start();

    channel_->set_read_event_callback([this] { do_read(); });
    channel_->reading();
}

timer_queue::~timer_queue() {
    channel_->reading(false);
    channel_->remove();

    close(fd_);
}

timer_id timer_queue::add_timer(timer_callback_t&& callback,
    time_point when,
    time_duration interval) {
    auto ptr = std::make_shared<timer>(std::move(callback), when, interval);
    ids_.insert(ptr->id());
    if (insert_timer(ptr)) {
        settime(ptr->when());
    }
    return ptr->id();
}

void timer_queue::remove_timer(timer_id id) {
    if (ids_.find(id) != ids_.end()) {
        ids_.erase(id);
    } else {
        log_warn << "timer id don't exisit";
    }
}

bool timer_queue::insert_timer(std::shared_ptr<timer> ptr) {
    bool changed = false;
    if (timers_.empty() || cmp{}(ptr, timers_.top())) {
        changed = true;
    }
    timers_.push(ptr);
    return changed;
}

void timer_queue::settime(time_point point) {
    itimerspec its{};
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(
        point - std::chrono::steady_clock::now())
                     .count();

    using namespace std::chrono_literals;
    its.it_value.tv_sec = nanos / (static_cast<long>(1000 * 1000 * 1000));
    its.it_value.tv_nsec = nanos % (static_cast<long>(1000 * 1000 * 1000));
    timerfd_settime(fd_, 0, &its, nullptr);
}

void timer_queue::do_read() {
    read_timerfd(fd_);

    auto now = std::chrono::steady_clock::now();
    auto timers = expired(now);

    do_run(timers);

    reset_timer(timers, now);
}

void timer_queue::do_run(const std::vector<std::shared_ptr<timer>>& timers) {
    for (int i = 0; i < timers.size(); ++i) {
        if (ids_.find(timers[i]->id()) != ids_.end()) {
            timers[i]->run();
        }
    }
}

std::vector<std::shared_ptr<timer>> timer_queue::expired(time_point point) {
    std::vector<std::shared_ptr<timer>> res;
    while (!timers_.empty() && timers_.top()->when() <= point) {
        res.push_back(timers_.top());
        timers_.pop();
    }
    return res;
}

void timer_queue::reset_timer(const std::vector<std::shared_ptr<timer>>& timers,
    time_point point) {
    for (int i = 0; i < timers.size(); ++i) {
        if (ids_.find(timers[i]->id()) != ids_.end()) {
            if (timers[i]->repeat()) {
                timers[i]->restart(point);
                insert_timer(timers[i]);
            } else {
                ids_.erase(timers[i]->id());
            }
        }
    }

    if (!timers_.empty()) {
        settime(timers_.top()->when());
    }
}

}  // namespace hestina
