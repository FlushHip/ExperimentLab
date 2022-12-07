#include "tcp_server.h"

#include "log/logger.h"

#include "acceptor.h"
#include "addr.h"
#include "channel.h"
#include "connection.h"
#include "eloop_thread_pool.h"
#include "event_loop.h"
#include "socket.h"

#include <iostream>
#include <memory>
#include <thread>

namespace hestina {
tcp_server::tcp_server(uint16_t port, std::string_view ip)
    : port_(port)
    , ip_(ip)
    , main_loop_thread_(std::make_unique<event_loop_thread>())
    , sub_loop_thread_pool_(std::make_unique<eloop_thread_pool>(
          std::thread::hardware_concurrency()))
    , acceptor_(std::make_unique<acceptor>(main_loop_thread_->get_eloop(),
          port,
          ip,
          true,
          true)) {
    acceptor_->set_new_connection_callback([this](auto&& sock) {
        new_connection(std::forward<decltype(sock)>(sock));
    });
    acceptor_->listen();
}

tcp_server::~tcp_server() = default;

bool tcp_server::start() {
    main_loop_thread_->start();
    sub_loop_thread_pool_->start();

    log_debug << "server ip : " << ip_ << " port : " << port_ << " running...";
    return true;
}
void tcp_server::new_connection(std::unique_ptr<socket>&& sock) {
    auto conn = std::make_shared<connection>(
        sub_loop_thread_pool_->get_eloop(), std::move(sock));
    conn->set_new_connection_callback(new_connection_callback_);
    conn->set_data_arrive_callback(data_arrive_callback_);
    conn->set_connection_close_callback([this](auto&& conn) {
        connection_close(std::forward<decltype(conn)>(conn));
    });

    connections_.emplace(conn);

    conn->established();
}

void tcp_server::connection_close(std::weak_ptr<connection>&& conn) {
    if (connection_close_callback_) {
        connection_close_callback_(conn);
    }
    if (!conn.expired()) {
        auto con = conn.lock();
        connections_.erase(con);
        con->closed();
    }
}

bool tcp_server::stop() {
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
