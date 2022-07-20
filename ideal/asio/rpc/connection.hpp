#pragma once

#include <boost/asio/buffer.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read.hpp>

#include <charconv>
#include <memory>
#include <queue>
#include <unordered_map>

#include "com_define.hpp"
#include "logger.hpp"

namespace rpc {
namespace detail {

class connection : public std::enable_shared_from_this<connection> {
public:
    explicit connection(boost::asio::io_context& io_context)
        : io_context_(io_context) {}

    boost::asio::ip::tcp::socket& socket() { return socket_; }

    void start() { do_read(); }

private:
    void do_read() {
        boost::asio::async_read(socket_,
            boost::asio::buffer(buffer_, detail::khead_length),
            [this](const boost::system::error_code& ec,
                std::size_t /*bytes_transfered*/) {
                if (!ec) {
                    int size = 0;
                    std::from_chars(buffer_.data(),
                        buffer_.data() + detail::khead_length, size);
                    if (size > 0 && size < detail::kbuffer_size) {
                        boost::asio::async_read(socket_,
                            boost::asio::buffer(buffer_, size),
                            [this](const boost::system::error_code& ec,
                                std::size_t bytes_transfered) {
                                if (!ec) {
                                    deal_data(buffer_, bytes_transfered);

                                    do_read();
                                } else if (ec != boost::asio::error::eof) {
                                    LOG_ERROR << ec.message();
                                } else {
                                    LOG_ERROR << ec.message();
                                    close();
                                }
                            });
                    } else {
                        LOG_ERROR << "invalid data length " << size;
                        close();
                    }
                } else if (ec != boost::asio::error::eof) {
                    LOG_ERROR << ec.message();
                    close();
                }
            });
    }

    template <typename Buffer>
    void deal_data(Buffer& buffer, std::size_t size) {
        LOG_INFO << std::string(buffer.data(), size);
    }

    void close() {
        boost::asio::post(io_context_, [this] {
            if (!socket_.is_open()) {
                return;
            }
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            socket_.close();
        });
        clear_cache();
    }

    void clear_cache() {
        while (!cache_messages_.empty()) {
            cache_messages_.pop();
        }
    }

private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket socket_{io_context_};

    std::array<char, detail::kbuffer_size> buffer_{0};

    std::queue<std::unique_ptr<detail::cache_context>> cache_messages_;
};

}  // namespace detail
}  // namespace rpc
