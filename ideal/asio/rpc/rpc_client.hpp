#pragma once

#include <boost/asio/buffer.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <boost/system/error_code.hpp>

#include <nlohmann/json.hpp>

#include <charconv>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <memory>
#include <mutex>
#include <sstream>
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <utility>

#include "logger.hpp"

namespace rpc {

namespace detail {

constexpr int kbuffer_size = 1 << 13;
constexpr int khead_length = 4;
constexpr int krequest_id_length = 8;

}  // namespace detail

using handler =
    std::function<void(const boost::system::error_code& ec, std::string_view)>;

class client {
public:
    client(const std::string& ip, std::uint16_t port) : ip_(ip), port_(port) {
        thread_ = std::thread([this] { io_context_.run(); });
    }

    ~client() {
        close();
        stop();
    }

    void close() {
        if (has_connected_) {
            // http://www.purecpp.org/detail?id=2303
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            socket_.close();
            has_connected_ = false;
        }
    }

    void stop() {
        io_context_.stop();
        if (thread_.joinable()) {
            thread_.join();
        }
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

    template <typename... Args>
    void async_call(const std::string& method,
        Args&&... args,
        handler handler) {
        if (!handler) {
            LOG_ERROR << "handler is nullptr";
        } else if (!has_connected_) {
            handler(boost::asio::error::not_connected, {});
        } else {
            auto call_ctx =
                std::make_shared<call_context>(io_context_, std::move(handler));
            std::unique_lock<std::mutex> lock(mutex_context_);
            call_context_map_[request_next_id_] = std::move(call_ctx);
            lock.unlock();

            do_write(request_next_id_, method, std::forward(args)...);

            ++request_next_id_;
        }
    }

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
                } else {
                    LOG_ERROR << ec.message();
                    close();
                }
            });
    }

    template <typename Buffer>
    void deal_data(Buffer& buffer, std::size_t size) {
        std::uint64_t request_id = 0;
        auto [_, ec] = std::from_chars(buffer.data(),
            buffer.data() + detail::krequest_id_length, request_id);
        if (ec != std::errc{}) {
            LOG_ERROR << std::make_error_code(ec).message();
        } else {
            auto begin = buffer.data() + detail::krequest_id_length;
            size -= detail::krequest_id_length;
            LOG_TRACE << "request response id : " << request_id
                      << ", data : " << std::string_view{begin, size};

            std::shared_ptr<call_context> call_context;
            {
                std::lock_guard<std::mutex> lock(mutex_context_);
                call_context = std::move(call_context_map_[request_id]);
            }
            if (!call_context) {
                LOG_ERROR << "invalid request response, id : " << request_id;
                return;
            }
            if (call_context->timeouted()) {
                call_context->callback(
                    boost::asio::error::timed_out, {begin, size});
            } else {
                call_context->cancel();
                call_context->callback(
                    boost::system::error_code{}, {begin, size});
            }
            std::lock_guard<std::mutex> lock(mutex_context_);
            call_context_map_.erase(request_id);
        }
    }

    template <typename... Args>
    void do_write(std::uint64_t request_id,
        const std::string& method,
        Args&&... args) {
        std::pair<std::string, std::tuple<Args...>> body_struct{
            method, std::forward_as_tuple(std::forward(args)...)};
        nlohmann::json body_json = body_struct;
        std::string body_str = body_json;

        // TODO(FlushHip) : buffers's data need restore
        std::vector<boost::asio::const_buffer> buffers;

        uint32_t data_size = detail::krequest_id_length + body_str.size();
        std::array<char, detail::khead_length> head_length_buff{0};
        std::to_chars(head_length_buff.data(),
            head_length_buff.data() + detail::khead_length, data_size);
        buffers.emplace_back(head_length_buff);

        std::array<char, detail::krequest_id_length> request_id_length_buff{0};
        std::to_chars(request_id_length_buff.data(),
            request_id_length_buff.data() + detail::krequest_id_length,
            request_id);
        buffers.emplace_back(request_id_length_buff);

        buffers.emplace_back(body_str);

        boost::asio::async_write(socket_, buffers,
            [this, request_id](const boost::system::error_code& ec,
                std::size_t bytes_transfered) {
                if (!ec) {
                    LOG_TRACE << "request id " << request_id
                              << ", send success, size bytes "
                              << bytes_transfered;
                } else {
                    LOG_ERROR << ec.message();
                    has_connected_ = false;
                }
            });
    }

private:
    class call_context : public std::enable_shared_from_this<call_context> {
    public:
        call_context(boost::asio::io_context& io_context, handler handler)
            : timer_(io_context, std::chrono::seconds(3))
            , handler_(std::move(handler)) {
            timer_.async_wait([this, self = shared_from_this()](
                                  const boost::system::error_code& ec) {
                if (!ec) {
                    timeouted_ = true;
                }
            });
        }

        void callback(const boost::system::error_code& ec,
            std::string_view data) {
            if (handler_) {
                handler_(ec, data);
            }
        }

        bool timeouted() const { return timeouted_; }

        void cancel() { timer_.cancel(); }

    private:
        boost::asio::steady_timer timer_;
        handler handler_;
        bool timeouted_ = false;
    };

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

    std::array<char, detail::kbuffer_size> buffer_{0};

    std::mutex mutex_context_;
    std::unordered_map<std::uint64_t, std::shared_ptr<call_context>>
        call_context_map_;

    std::atomic<std::uint64_t> request_next_id_{0};
};

}  // namespace rpc
