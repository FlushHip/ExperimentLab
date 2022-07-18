#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <unordered_map>

namespace rpc {
namespace detail {

class connection : public std::enable_shared_from_this<connection> {
public:
    explicit connection(boost::asio::io_context& io_context)
        : io_context_(io_context) {}

    boost::asio::ip::tcp::socket& socket() { return socket_; }

    void start() {}

private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket socket_{io_context_};
};

}  // namespace detail
}  // namespace rpc
