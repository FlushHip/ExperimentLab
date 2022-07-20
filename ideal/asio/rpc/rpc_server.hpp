#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/system/error_code.hpp>

#include <memory>
#include <string_view>

#include "connection.hpp"
#include "io_context_pool.hpp"
#include "logger.hpp"

namespace rpc {

class server {
public:
    server(const std::string& ip, std::uint16_t port) : ip_(ip), port_(port) {
        using namespace std::literals::string_view_literals;
        assert(ip == "127.0.0.1"sv || ip == "0.0.0.0"sv);
    }

    void run() {
        deal_signal();
        init_acceptor();

        io_context_pool_.run();
    }

    void stop() { io_context_pool_.stop(); }

    void close() { stop(); }

private:
    void deal_signal() {
        signals_.add(SIGINT);
        signals_.add(SIGTERM);
#ifdef SIGQUIT
        signals_.add(SIGQUIT);
#endif
        signals_.async_wait(
            [this](const boost::system::error_code& ec, int signal_number) {
                LOG_INFO << ec.message() << "signal_number : " << signal_number;
                stop();
            });
    }

    void init_acceptor() {
        boost::asio::ip::tcp::endpoint endpoint{
            boost::asio::ip::address_v4::from_string(ip_), port_};
        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(
            boost::asio::ip::tcp::acceptor::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();

        LOG_INFO << "rpc server start, ip : " << ip_ << ", port : " << port_;

        do_accept();
    }

    void do_accept() {
        auto session =
            std::make_shared<detail::connection>(io_context_pool_.io_context());
        acceptor_.async_accept(session->socket(),
            [this, session](const boost::system::error_code& ec) {
                if (!ec) {
                    ++connection_id_;
                    connections_[connection_id_] = session;
                    LOG_INFO << "new connection, id : " << connection_id_
                             << ", remote endpoint "
                             << boost::lexical_cast<std::string>(
                                    session->socket().remote_endpoint());

                    session->start();

                } else {
                    LOG_ERROR << ec.message();
                }

                do_accept();
            });
    }

private:
    detail::io_context_pool io_context_pool_{};
    boost::asio::signal_set signals_{io_context_pool_.io_context()};
    boost::asio::ip::tcp::acceptor acceptor_{io_context_pool_.io_context()};

    std::string ip_;
    std::uint16_t port_;

    std::uint64_t connection_id_{0};
    std::unordered_map<std::uint64_t, std::shared_ptr<detail::connection>>
        connections_;
};

}  // namespace rpc
