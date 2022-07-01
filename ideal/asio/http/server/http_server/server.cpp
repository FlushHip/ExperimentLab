#include "server.hpp"

#include <signal.h>

#include <spdlog/spdlog.h>

namespace http {
namespace server {

HttpServer::HttpServer(std::string_view address, std::string_view port, std::string_view doc_root)
    : io_context_()
    , acceptor_(io_context_)
    , signals_(io_context_)
    , request_handler_(doc_root)
{
    signals_.add(SIGINT);
    signals_.add(SIGTERM);
#ifdef SIGQUIT
    signals_.add(SIGQUIT);
#endif
    signals_.async_wait(std::bind(&HttpServer::handle_stop, this));

    boost::asio::ip::tcp::resolver resolver(io_context_);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(address, port).begin();

    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    SPDLOG_INFO("Server ip : {}, port : {}, doc_root : {}", endpoint.address().to_string(), endpoint.port(), doc_root);

    do_accept();
}

void HttpServer::run()
{
    io_context_.run();
}

void HttpServer::do_accept()
{
    auto new_connection = std::make_shared<Connection>(io_context_
        , connection_manager_, request_handler_);
    acceptor_.async_accept(new_connection->socket(), [connection = new_connection, this] (const boost::system::error_code &ec)
    {
        if (!acceptor_.is_open()) {
            spdlog::error("Server acceptor is close");
            return;
        }

        if (!ec) {
            auto remote_endpoint = connection->socket().remote_endpoint();
            SPDLOG_INFO("new connection, ip : {}, port : {}", remote_endpoint.address().to_string(), remote_endpoint.port());
            connection->start();
        } else {
            spdlog::critical(ec.message());
        }

        do_accept();
    });
}

void HttpServer::handle_stop()
{
    acceptor_.close();
    connection_manager_.stop_all();
}

}
}
