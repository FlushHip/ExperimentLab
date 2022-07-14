#pragma once

#include <boost/asio/buffer.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read.hpp>
#include <boost/system/error_code.hpp>

#include <condition_variable>
#include <cstddef>
#include <memory>
#include <mutex>
#include <thread>

#include "logger.hpp"

namespace rpc {

namespace detail {

constexpr int kbuffer_size = 1 << 13;
constexpr int khead_length = 4;

}  // namespace detail

class client {
public:
    client(const std::string& ip, std::uint16_t port) : ip_(ip), port_(port) {
        thread_ = std::thread([this] { io_context_.run(); });
    }

    ~client() { close(); }

    void close() {
        // http://www.purecpp.org/detail?id=2303
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket_.close();
        has_connected_ = false;
    }

    bool connect() {
        async_connect();

        std::unique_lock<std::mutex> lock(mutex_async_connect_);
        using namespace std::literals::chrono_literals;
        cv_async_connect_.wait_for(
            lock, 3s, [this] { return has_connected_.load(); });
        return has_connected_;
    }

    void async_connect() {
        auto ip = boost::asio::ip::address_v4::from_string(ip_);
        socket_.async_connect(
            {ip, port_}, [this](const boost::system::error_code& ec) {
                if (!ec) {
                    do_read();

                    cv_async_connect_.notify_all();
                } else {
                    LOG_ERROR << ec.message();

                    has_connected_ = false;
                }
            });
    }

private:
    void do_read() {
        boost::asio::async_read(socket_,
            boost::asio::buffer(buffer_, detail::khead_length),
            [this](const boost::system::error_code& ec,
                std::size_t bytes_transfered) {
                if (!ec) {
                } else {
                    LOG_ERROR << ec.message();
                }
            });
    }

private:
    boost::asio::io_context io_context_{1};
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type>
        guard_{boost::asio::make_work_guard(io_context_)};
    boost::asio::ip::tcp::socket socket_{io_context_};

    std::string ip_;
    std::uint16_t port_;

    std::thread thread_;

    std::mutex mutex_async_connect_;
    std::condition_variable cv_async_connect_;
    std::atomic_bool has_connected_{false};

    std::array<char, detail::kbuffer_size> buffer_;
};

}  // namespace rpc
