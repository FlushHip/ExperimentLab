#include "tcp_server.h"

#include "acceptor.h"
#include "addr.h"
#include "channel.h"
#include "connection.h"
#include "event_loop.h"
#include "socket.h"

#include <iostream>
#include <memory>

namespace hestina {
tcp_server::tcp_server(uint16_t port, std::string_view ip)
    : port_(port)
    , ip_(ip)
    , event_loop_(std::make_unique<event_loop>())
    , acceptor_(
          std::make_unique<acceptor>(event_loop_.get(), port, ip, true, true)) {
    acceptor_->set_new_connection_callback([this](auto&& sock) {
        new_connection(std::forward<decltype(sock)>(sock));
    });
    acceptor_->listen();
}

tcp_server::~tcp_server() = default;

bool tcp_server::start() {
    std::cerr << "server ip : " << ip_ << " port : " << port_ << " running..."
              << std::endl;
    thread_ = std::thread([this] { event_loop_->run(); });
    return true;
}
void tcp_server::new_connection(std::unique_ptr<socket>&& sock) {
    std::cerr << "new connection..." << std::endl;

    auto conn =
        std::make_shared<connection>(event_loop_.get(), std::move(sock));
    conn->set_new_connection_callback(new_connection_callback_);
    conn->set_data_arrive_callback(data_arrive_callback_);
    conn->set_connection_close_callback(connection_close_callback_);

    connections_.emplace(conn);

    conn->established();
}

bool tcp_server::stop() {
    if (thread_.joinable()) {
        thread_.join();
    }
    return true;
}
void tcp_server::set_new_connection_callback(
    new_connection_callback_t&& callback) {
    new_connection_callback_ = std::move(callback);
}

void tcp_server::set_data_arrive_callback(data_arrive_callback_t&& callback) {
    data_arrive_callback_ = std::move(callback);
}

void tcp_server::set_connection_close_callback(
    connection_close_callback_t&& callback) {
    connection_close_callback_ = std::move(callback);
}

}  // namespace hestina
