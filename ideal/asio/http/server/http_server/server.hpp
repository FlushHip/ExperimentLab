#pragma once

#include <string_view>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

#include "connection.hpp"
#include "connection_manager.hpp"
#include "request_handler.hpp"

namespace http {
namespace server {

class HttpServer : public boost::noncopyable
{
public:
    explicit HttpServer(std::string_view address, std::string_view port, std::string_view doc_root);

    void run();

private:
    void do_accept();

    void handle_stop();
private:
    boost::asio::io_context io_context_;
    boost::asio::signal_set signals_;
    boost::asio::ip::tcp::acceptor acceptor_;

    ConnectionManager connection_manager_;
    RequestHandler request_handler_;
};

}
}
