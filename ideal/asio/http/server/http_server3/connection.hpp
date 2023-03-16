#pragma once

#include <memory>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

#include "request.hpp"
#include "request_parser.hpp"
#include "reply.hpp"

namespace http {
namespace server {

class ConnectionManager;
class RequestHandler;

class Connection
    : public std::enable_shared_from_this<Connection>
    , public boost::noncopyable
{
public:
    Connection(boost::asio::io_context &io_context
        , ConnectionManager &connection_manager
        , RequestHandler &request_handler);

    boost::asio::ip::tcp::socket& socket() { return socket_; };

    void start();
    void stop();

private:
    void handle_read(const boost::system::error_code &ec, std::size_t size);
    void handle_write(const boost::system::error_code &ec);

private:
    boost::asio::ip::tcp::socket socket_;

    enum { kBuffLength = 1 << 13 };
    std::array<uint8_t, kBuffLength> buffer_;

    ConnectionManager &connection_manager_;
    RequestHandler &request_handler_;

    Request request_;
    RequestParser requset_parser_;
    Reply reply_;
};

using ConnectionPtr = std::shared_ptr<Connection>;

}
}
