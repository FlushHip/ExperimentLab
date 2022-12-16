#include "poller.h"

#include "channel.h"
#include "log/logger.h"

#include <sys/epoll.h>

#include <cassert>

namespace hestina {

namespace {
constexpr const int kpoll_wait_ms = 1000;
}  // namespace

poller::poller() : fd_(epoll_create1(0)) {
    assert(fd_ != -1);
}

poller::~poller() {
    close(fd_);
};

std::vector<channel*> poller::poll() {
    int nums =
        epoll_wait(fd_, events_.data(), max_events_length, kpoll_wait_ms);

    std::vector<channel*> ret;
    if (nums < 0 && errno == EINTR) {
        return ret;
    }
    for (int i = 0; i < nums; ++i) {
        auto* channel = static_cast<class channel*>(events_[i].data.ptr);
        channel->ready_events_ = events_[i].events;
        ret.push_back(channel);
    }
    return ret;
}

void poller::update_channel(channel* channel) {
    assert(channel != nullptr);
    if (!channel->is_add_) {
        update(EPOLL_CTL_ADD, channel);
        channel->is_add_ = true;
    } else {
        update(EPOLL_CTL_MOD, channel);
    }
}

void poller::remove_channel(channel* channel) {
    assert(channel != nullptr);
    if (channel->is_add_) {
        update(EPOLL_CTL_DEL, channel);
        channel->is_add_ = false;
    }
}

void poller::update(int op, channel* channel) {
    epoll_event event{
        channel->listen_events(),
        channel,
    };
    int ret = epoll_ctl(fd_, op, channel->fd(), &event);
    assert(ret != -1);
}

}  // namespace hestina
