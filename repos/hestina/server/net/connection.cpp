#include "connection.h"

#include "channel.h"
#include "socket.h"

#include <iostream>

namespace hestina {

connection::connection(event_loop* loop, std::unique_ptr<socket>&& sock)
    : socket_(std::move(sock))
    , channel_(std::make_unique<channel>(loop, socket_->fd())) {
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
    char buff[buff_length + 1 + 4] = {0};
    while (true) {
        auto n = read(socket_->fd(), buff, buff_length);
        if (n > 0) {
            buff[n] = '_';
            buff[n + 1] = 'd';
            buff[n + 2] = 'u';
            buff[n + 3] = 'p';
            buff[n + 4] = '\0';
            std::cerr << "recv : "
                      << std::string_view{buff,
                             static_cast<std::string_view::size_type>(n)}
                      << std::endl;
            write(socket_->fd(), buff, n + 4);
        } else if (n == 0) {
            std::cerr << "recv : EOF" << std::endl;
            close(socket_->fd());
            break;
        } else if (n == -1 && errno == EINTR) {
            std::cerr << "continue..." << std::endl;
            continue;
        } else if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            std::cerr << "finish once read" << std::endl;
            break;
        }
    }
}

void connection::do_close() {}

void connection::do_error() {}

}  // namespace hestina
