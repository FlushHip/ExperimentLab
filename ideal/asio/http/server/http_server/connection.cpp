#include "connection.hpp"

#include <spdlog/spdlog.h>

#include "connection_manager.hpp"
#include "request_handler.hpp"
namespace http {
namespace server {

Connection::Connection(boost::asio::io_context &io_context
    , ConnectionManager &connection_manager
    , RequestHandler &request_handler)
    : socket_(io_context)
    , connection_manager_(connection_manager)
    , request_handler_(request_handler)
{

}


void Connection::start()
{
    socket_.async_read_some(boost::asio::buffer(buffer_), std::bind(&Connection::handle_read, shared_from_this()
        , std::placeholders::_1, std::placeholders::_2));
}

void Connection::stop()
{
    socket_.close();
}

void Connection::handle_read(const boost::system::error_code &ec, std::size_t size)
{
    if (!ec) {
        auto [result, _] = requset_parser_.parse(request_, buffer_.data(), buffer_.data() + size);
        if (result) {
            SPDLOG_DEBUG("request header : {}", requset_parser_.raw_string());
            request_handler_.handle_request(request_, reply_);
            boost::asio::async_write(socket_, reply_.to_buffers(), std::bind(&Connection::handle_write, shared_from_this()
                , std::placeholders::_1));
        } else if (!result) {
            SPDLOG_DEBUG("request header : {}", requset_parser_.raw_string());
            reply_ = Reply::stock_reply(Reply::bad_request);
            boost::asio::async_write(socket_, reply_.to_buffers(), std::bind(&Connection::handle_write, shared_from_this()
                , std::placeholders::_1));
        } else {
            socket_.async_read_some(boost::asio::buffer(buffer_), std::bind(&Connection::handle_read, shared_from_this()
                , std::placeholders::_1, std::placeholders::_2));
        }
    } else if (ec != boost::asio::error::operation_aborted) {
        connection_manager_.stop(shared_from_this());
    }
}

void Connection::handle_write(const boost::system::error_code &ec)
{
    if (!ec) {
        boost::system::error_code ignored_ec;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
    } else if (ec != boost::asio::error::operation_aborted) {
        connection_manager_.stop(shared_from_this());
    }
}

}
}
