#include <spdlog/spdlog.h>

#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/ssl/stream_base.hpp>
#include <boost/asio/write.hpp>


#include <boost/asio/error.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/system/error_code.hpp>

#include <memory>

namespace tcp {
namespace ssl {

class session : public std::enable_shared_from_this<session> {
public:
    session(boost::asio::io_context& io_context, boost::asio::ssl::context& ctx)
        : socket_(io_context, ctx) {}

    auto& socket() { return socket_.lowest_layer(); }

    void start() {
        socket_.async_handshake(boost::asio::ssl::stream_base::server,
            std::bind(
                [this](const boost::system::error_code& ec) {
                    if (!ec) {
                        do_read();
                    } else
                        SPDLOG_ERROR(ec.message());
                },
                std::placeholders::_1));
    }

private:
    void do_read() {
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
            [this](
                const boost::system::error_code& ec, size_t bytes_transferred) {
                if (!ec) {
                    do_write(bytes_transferred);
                } else if (boost::asio::ssl::error::stream_truncated != ec) {
                    SPDLOG_ERROR(ec.message());
                }
            });
    }

    void do_write(size_t bytes_transferred) {
        boost::asio::async_write(socket_,
            boost::asio::buffer(data_, bytes_transferred),
            [this](
                const boost::system::error_code& ec, size_t bytes_transferred) {
                if (!ec) {
                    do_read();
                } else {
                    SPDLOG_ERROR(ec.message());
                }
            });
    }

private:
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;

    enum { max_length = 1024 };
    char data_[max_length];
};

class server {
public:
    server()
        : io_context_(1)
        , acceptor_(io_context_,
              boost::asio::ip::tcp::endpoint(
                  boost::asio::ip::address::from_string("127.0.0.1"),
                  55555))
        , ctx_(boost::asio::ssl::context::sslv23) {
        ctx_.set_options(boost::asio::ssl::context::default_workarounds |
            boost::asio::ssl::context::no_sslv2 |
            boost::asio::ssl::context::single_dh_use);
        using namespace std::literals::string_literals;
        ctx_.set_password_callback(std::bind([] { return "test"s; }));
        ctx_.use_certificate_chain_file("server.pem");
        ctx_.use_private_key_file(
            "server.pem", boost::asio::ssl::context::file_format::pem);
        ctx_.use_tmp_dh_file("dh2048.pem");

        acceptor_.set_option(
            boost::asio::ip::tcp::acceptor::reuse_address(true));
        do_accept();
    }

    void run() { io_context_.run(); }

    void do_accept() {
        auto new_session = std::make_shared<session>(io_context_, ctx_);
        acceptor_.async_accept(new_session->socket(),
            [new_session, this](const boost::system::error_code& ec) {
                if (!ec) {
                    SPDLOG_DEBUG("...new connection");
                    new_session->start();
                    sessions_.push_back(new_session);
                } else {
                    SPDLOG_ERROR(ec.message());
                }
                do_accept();
            });
    }

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ssl::context ctx_;

    std::vector<std::shared_ptr<session>> sessions_;
};

}  // namespace ssl
}  // namespace tcp

int main(int argc, char* argv[]) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %T.%e][%-5t][%^%l%$][%s.%!:%#] %v");

    try {
        tcp::ssl::server server;
        server.run();
    } catch (const std::exception& e) {
        SPDLOG_ERROR(e.what());
    }

    return 0;
}
