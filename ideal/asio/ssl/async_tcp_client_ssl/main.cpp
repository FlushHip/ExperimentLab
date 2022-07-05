#include <boost/asio/buffer.hpp>
#include <boost/asio/completion_condition.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/ssl/stream_base.hpp>
#include <boost/asio/ssl/verify_context.hpp>
#include <boost/asio/ssl/verify_mode.hpp>
#include <boost/asio/write.hpp>
#include <boost/system/error_code.hpp>

#include <charconv>
#include <exception>
#include <iostream>
#include <string_view>

#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <spdlog/spdlog.h>

namespace tcp {
namespace ssl {

class client {
public:
    client(boost::asio::io_context& io_context)
        : resolver_(io_context)
        , ctx_(boost::asio::ssl::context::sslv23)
        , socket_(io_context, ctx_) {
        ctx_.load_verify_file("ca.pem");
        ctx_.set_verify_mode(boost::asio::ssl::verify_peer);
        ctx_.set_verify_callback(std::bind(&client::verify_certificate, this,
            std::placeholders::_1, std::placeholders::_2));

        using namespace std::literals::string_view_literals;
        resolver_.async_resolve("localhost"sv, "55555"sv,
            [this](const boost::system::error_code& ec,
                boost::asio::ip::tcp::resolver::results_type endpoints) {
                boost::asio::async_connect(socket_.lowest_layer(), endpoints,
                    std::bind(
                        [this](const boost::system::error_code& ec) {
                            if (!ec) {
                                socket_.async_handshake(
                                    boost::asio::ssl::stream_base::client,
                                    std::bind(
                                        [this](const boost::system::error_code&
                                                ec) {
                                            if (!ec)
                                                do_write();
                                            else
                                                SPDLOG_ERROR(ec.message());
                                        },
                                        std::placeholders::_1));
                            } else {
                                SPDLOG_ERROR(ec.message());
                            }
                        },
                        std::placeholders::_1));
            });
    }

private:
    bool verify_certificate(bool preverified,
        boost::asio::ssl::verify_context& ctx) {
        char subject_name[256] = {0};
        auto cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
        X509_NAME_oneline(
            X509_get_subject_name(cert), subject_name, sizeof(subject_name));
        SPDLOG_DEBUG("Verifying {}", subject_name);
        return preverified;
    }

    void do_write() {
        boost::asio::async_write(socket_, boost::asio::buffer(request_),
            [this](
                const boost::system::error_code& ec, size_t bytes_transferred) {
                if (!ec) {
                    boost::asio::async_read(socket_,
                        boost::asio::buffer(reply_),
                        boost::asio::transfer_at_least(bytes_transferred),
                        [this](const boost::system::error_code& ec,
                            size_t bytes_transferred) {
                            if (!ec) {
                                SPDLOG_INFO(
                                    std::string(reply_, bytes_transferred));
                            } else
                                SPDLOG_ERROR(ec.message());
                        });
                } else
                    SPDLOG_ERROR(ec.message());
            });
    }

private:
    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::ssl::context ctx_;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;

    enum { max_length = 1024 };

    char request_[max_length] = "flushhip";
    char reply_[max_length] = {0};
};

}  // namespace ssl
}  // namespace tcp

int main(int argc, char* argv[]) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %T.%e][%-5t][%^%l%$][%s.%!:%#] %v");

    try {
        boost::asio::io_context io_context(1);
        tcp::ssl::client client(io_context);
        io_context.run();
    } catch (const std::exception& e) {
        SPDLOG_ERROR(e.what());
    }

    return 0;
}
