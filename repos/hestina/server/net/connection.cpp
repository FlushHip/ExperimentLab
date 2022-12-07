#include "connection.h"
#include <unistd.h>

#include "log/logger.h"

#include "addr.h"
#include "buffer.h"
#include "channel.h"
#include "socket.h"

#include <cassert>
#include <cstring>
#include <iostream>

namespace hestina {

connection::connection(event_loop* loop, std::unique_ptr<socket>&& sock)
    : socket_(std::move(sock))
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

    log_debug << "new connection established, " << local_addr_->port() << " <- "
              << peer_addr_->point();
    assert(status_ == status::connecting);
    status_ = status::connected;
    if (new_connection_callback_) {
        new_connection_callback_(shared_from_this());
    }
}

void connection::closed() {
    assert(status_ == status::disconnecting);
    channel_->writing(false);

    channel_->remove();
    status_ = status::disconnected;

    log_debug << "connection closed, " << local_addr_->port() << " <- "
              << peer_addr_->point();
}

void connection::set_new_connection_callback(
    const new_connection_callback_t& callback) {
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
    constexpr int buff_length = 1024;
    thread_local char sbuff[buff_length + 1 + 4] = {0};
    buffer_->clear();
    while (true) {
        int n = socket_->read(sbuff, buff_length);
        if (n > 0) {
            buffer_->append({sbuff, static_cast<size_t>(n)});
        } else if (n == 0) {
            do_close();
            break;
        } else if (n == -1 && errno == EINTR) {
            continue;
        } else if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            read_finished();
            break;
        }
    }
}

void connection::read_finished() {
    log_trace << "recv <-- " << peer_addr_->point() << ": " << buffer_->data();
    if (data_arrive_callback_) {
        data_arrive_callback_(shared_from_this(), buffer_->data());
    }
}

void connection::send(std::string_view data) {
    log_trace << "send --> " << peer_addr_->point() << ": " << data;
    write(socket_->fd(), data.data(), data.size());
    socket_->write(data.data(), data.size());
}

const addr& connection::local_addr() const {
    return *local_addr_;
}

const addr& connection::peer_addr() const {
    return *peer_addr_;
}

void connection::do_close() {
    assert(status_ == status::connected);
    status_ = status::disconnecting;

    channel_->reading(false);
    if (connection_close_callback_) {
        connection_close_callback_(shared_from_this());
    }
}

void connection::do_error() {
    int err = socket_->last_error();
    if (err != 0) {
        log_error << "fd " << socket_->fd() << " err " << err
                  << " msg : " << strerror(err);
    }
}

}  // namespace hestina
