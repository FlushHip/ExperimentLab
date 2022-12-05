#include "connection.h"

#include "buffer.h"
#include "channel.h"
#include "socket.h"

#include <cassert>
#include <iostream>

namespace hestina {

connection::connection(event_loop* loop, std::unique_ptr<socket>&& sock)
    : socket_(std::move(sock))
    , channel_(std::make_unique<channel>(loop, socket_->fd()))
    , buffer_(std::make_unique<buffer>()) {
    channel_->set_read_event_callback([this] { do_read(); });
    channel_->set_close_event_callback([this] { do_close(); });
    channel_->set_error_event_callback([this] { do_error(); });
}

connection::~connection() = default;

void connection::established() {
    channel_->enable_reading();

    if (new_connection_callback_) {
        new_connection_callback_(shared_from_this());
    }
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
    while (true) {
        auto n = read(socket_->fd(), sbuff, buff_length);
        if (n > 0) {
            buffer_->append({sbuff, static_cast<size_t>(n)});
        } else if (n == 0) {
            close(socket_->fd());
            if (connection_close_callback_) {
                connection_close_callback_(shared_from_this());
            }
            buffer_->clear();
            break;
        } else if (n == -1 && errno == EINTR) {
            std::cerr << "continue..." << std::endl;
            continue;
        } else if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            if (data_arrive_callback_) {
                data_arrive_callback_(shared_from_this(), buffer_->data());
            }
            buffer_->clear();
            break;
        }
    }
}
void connection::send(std::string_view data) {
    write(socket_->fd(), data.data(), data.size());
}

void connection::do_close() {}

void connection::do_error() {}

}  // namespace hestina
