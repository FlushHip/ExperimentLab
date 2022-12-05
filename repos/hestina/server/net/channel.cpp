#include "channel.h"

#include "event_loop.h"

#include <sys/epoll.h>

namespace hestina {

channel::channel(event_loop* loop, int fd)
    : loop_(loop), fd_(fd), listen_events_(0) {}

channel::~channel() = default;

int channel::fd() const {
    return fd_;
}

uint32_t channel::listen_events() const {
    return listen_events_;
}

uint32_t channel::ready_events() const {
    return ready_events_;
}

void channel::enable_reading() {
    listen_events_ |= (EPOLLIN | EPOLLPRI);
    update();
}

void channel::enable_writing() {
    listen_events_ |= EPOLLOUT;
    update();
}

void channel::disable_reading() {
    listen_events_ &= ~(EPOLLIN | EPOLLPRI);
    update();
}

void channel::disable_writing() {
    listen_events_ &= ~EPOLLOUT;
    update();
}

void channel::enable_et() {
    listen_events_ |= EPOLLET;
    update();
}

void channel::disable_et() {
    listen_events_ &= ~EPOLLET;
    update();
}

void channel::update() {
    loop_->update_channel(this);
}

void channel::set_any_event_callback(event_callback_t&& callback) {
    any_event_callback_ = std::move(callback);
}

void channel::set_read_event_callback(event_callback_t&& callback) {
    read_event_callback_ = std::move(callback);
}

void channel::set_write_event_callback(event_callback_t&& callback) {
    write_event_callback_ = std::move(callback);
}

void channel::set_close_event_callback(event_callback_t&& callback) {
    close_event_callback_ = std::move(callback);
}

void channel::set_error_event_callback(event_callback_t&& callback) {
    error_event_callback_ = callback;
}

void channel::handle_event() {
    if (any_event_callback_) {
        any_event_callback_();
        return;
    }

    if (ready_events_ & EPOLLHUP) {
        if (close_event_callback_) {
            close_event_callback_();
        }
    }
    if (ready_events_ & EPOLLERR) {
        if (error_event_callback_) {
            error_event_callback_();
        }
    }
    if (ready_events_ & (EPOLLIN | EPOLLPRI)) {
        if (read_event_callback_) {
            read_event_callback_();
        }
    }
    if (ready_events_ & EPOLLOUT) {
        if (write_event_callback_) {
            write_event_callback_();
        }
    }
}

}  // namespace hestina
