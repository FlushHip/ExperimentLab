#include "connection.h"

#include <hestina/timer/timer_queue.h>
#include "log/logger.h"

#include "addr.h"
#include "buffer.h"
#include "channel.h"
#include "socket.h"

#include <unistd.h>

#include <cassert>
#include <chrono>
#include <cstring>
#include <iostream>
#include <memory>

namespace hestina {

std::atomic_uint64_t connection::sid_index = 0;

connection::connection(event_loop* loop,
    std::unique_ptr<socket>&& sock,
    peer_type_t type)
    : id_(++sid_index)
    , peer_type_(type)
    , socket_(std::move(sock))
    , channel_(std::make_unique<channel>(loop, socket_->fd()))
    , local_addr_(socket_->local_addr())
    , peer_addr_(socket_->peer_addr())
    , buffer_(std::make_unique<buffer>()) {
    socket_->nonblocking();
    channel_->et();

    channel_->set_read_event_callback([this] { do_read(); });
    channel_->set_close_event_callback([this] { do_close(); });
    channel_->set_error_event_callback([this] { do_error(); });
}

connection::~connection() = default;

void connection::established() {
    channel_->reading();

    if (peer_type_ == peer_type_t::client) {
        log_debug << "new connection " << id_ << ", established, "
                  << local_addr_->port() << " <- " << peer_addr_->point();
    } else {
        log_debug << "new connection " << id_ << ", established, "
                  << local_addr_->port() << " -> " << peer_addr_->point();
    }
    assert(status_ == status_t::connecting);
    status_ = status_t::connected;
    if (new_connection_callback_) {
        new_connection_callback_(shared_from_this());
    }
}

void connection::closed() {
    if (status_ == status_t::disconnecting) {
        channel_->writing(false);

        channel_->remove();
        status_ = status_t::disconnected;

        if (peer_type_ == peer_type_t::client) {
            log_debug << "connection " << id_ << ", closed, "
                      << local_addr_->port() << " <- " << peer_addr_->point();
        } else {
            log_debug << "connection " << id_ << ", closed, "
                      << local_addr_->port() << " -> " << peer_addr_->point();
        }
    }
}

void connection::shutdown() {
    if (status_ == status_t::connected) {
        status_ = status_t::disconnecting;

        channel_->reading(false);
        if (connection_close_callback_) {
            connection_close_callback_(shared_from_this());
        }
    }
}

void connection::idle_timeout(size_t timeout, timer_queue* timer_que) {
    idle_timeout_ = timeout;
    idle_timer_ = timer_que;

    extend_life();
}

void connection::extend_life() {
    if (idle_timeout_ > 0) {
        if (last_timer_update_point_ + std::chrono::seconds(1) <=
            std::chrono::steady_clock::now()) {
            return;
        }

        last_timer_update_point_ = std::chrono::steady_clock::now();

        if (last_timer_id_ != timer::sinvalid_id) {
            idle_timer_->remove_timer(last_timer_id_);
        }
        std::weak_ptr<connection> self_weak = shared_from_this();
        last_timer_id_ = idle_timer_->add_timer(
            [self_weak] {
                if (auto self = self_weak.lock()) {
                    self->close();
                }
            },
            std::chrono::steady_clock::now() +
                std::chrono::seconds(idle_timeout_));
    }
}

void connection::close() {
    shutdown();

    closed();
}

void connection::set_connection_establish_callback(
    const connection_establish_callback_t& callback) {
    new_connection_callback_ = callback;
}

void connection::set_data_arrive_callback(
    const data_arrive_callback_t& callback) {
    data_arrive_callback_ = callback;
}

void connection::set_connection_close_callback(
    const connection_close_callback_t& callback) {
    connection_close_callback_ = callback;
}

void connection::do_read() {
    while (true) {
        int err = 0;
        int n = buffer_->read_fd(socket_->fd(), err);
        if (n > 0) {
            // buffer_->append({sbuff, static_cast<size_t>(n)});
        } else if (n == 0) {
            do_close();
            break;
        } else if (n == -1 && err == EINTR) {
            continue;
        } else if (n == -1 && (err == EAGAIN || err == EWOULDBLOCK)) {
            read_finished();
            break;
        }
    }
}

void connection::read_finished() {
    log_trace << "conn " << id_ << ", recv <-- " << peer_addr_->point() << ": "
              << buffer_->peek();

    extend_life();

    if (data_arrive_callback_) {
        data_arrive_callback_(shared_from_this(), buffer_.get());
    }
}

void connection::send(std::string_view data) {
    log_trace << "conn " << id_ << ", send --> " << peer_addr_->point() << ": "
              << data;

    extend_life();

    socket_->write(data.data(), data.size());
}

const addr& connection::local_addr() const {
    return *local_addr_;
}

const addr& connection::peer_addr() const {
    return *peer_addr_;
}

void connection::do_close() {
    shutdown();
}

void connection::do_error() {
    int err = socket_->last_error();
    if (err != 0) {
        log_error << "connection " << id_ << ", fd " << socket_->fd() << " err "
                  << err << " msg : " << strerror(err);
    }
}

connection::status_t connection::status() const {
    return status_;
}

uint64_t connection::id() const {
    return id_;
}

}  // namespace hestina
