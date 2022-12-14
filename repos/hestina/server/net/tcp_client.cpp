#include "tcp_client.h"

#include "net/addr.h"
#include "net/callback.h"
#include "net/channel.h"
#include "net/connection.h"
#include "net/connector.h"
#include "net/eloop_thread_pool.h"
#include "net/socket.h"

namespace hestina {

tcp_client::tcp_client() : loop_thread_(std::make_unique<event_loop_thread>()) {
    loop_thread_->start();
}

bool tcp_client::connect(std::string_view ip, uint16_t port, bool async) {
    if (is_connect_) {
        close();
    }

    connector_ =
        std::make_unique<connector>(loop_thread_->get_eloop(), ip, port);
    connector_->set_connect_finish_callback([this](auto&& sock) {
        connect_fishsh(std::forward<decltype(sock)>(sock));
    });
    connector_->connect();
    return true;
}

tcp_client::~tcp_client() {
    close();
}

void tcp_client::connect_fishsh(std::unique_ptr<socket>&& sock) {
    connection_ = std::make_shared<connection>(loop_thread_->get_eloop(),
        std::move(sock), connection::peer_type_t::server);
    connection_->set_connection_establish_callback(
        connection_establish_callback_);
    connection_->set_data_arrive_callback(data_arrive_callback_);
    connection_->set_connection_close_callback([this](auto&& conn) {
        connect_close(std::forward<decltype(conn)>(conn));
    });

    connection_->established();

    is_connect_ = true;

    connector_.reset();
}

void tcp_client::connect_close(std::weak_ptr<connection> conn) {
    if (connection_close_callback_) {
        connection_close_callback_(conn);
    }
    if (auto con = conn.lock()) {
        con->closed();
    }
}

void tcp_client::set_connection_establish_callback(
    connection_establish_callback_t&& callback) {
    connection_establish_callback_ = std::move(callback);
}

void tcp_client::set_data_arrive_callback(data_arrive_callback_t&& callback) {
    data_arrive_callback_ = std::move(callback);
}

void tcp_client::set_connection_close_callback(
    connection_close_callback_t&& callback) {
    connection_close_callback_ = std::move(callback);
}

void tcp_client::close() {
    connector_.reset();
    if (is_connect_ && connection_) {
        connection_->shutdown();
        connection_.reset();
    }

    is_connect_ = false;
}

}  // namespace hestina
