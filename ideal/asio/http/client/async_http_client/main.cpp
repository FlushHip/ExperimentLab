#include <iostream>
#include <string_view>

#include <boost/asio.hpp>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>

class HttpClient
{
public:
    HttpClient(boost::asio::io_context &io_context, std::string_view http_root, std::string_view http_path)
        : io_context_(io_context)
        , resolver_(io_context)
        , socket_(io_context)
    {
        std::ostream request_stream(&request_);

        request_stream << "GET " << http_path << " HTTP/1.0\r\n";
        request_stream << "Host: " << http_root << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        auto endpoints = resolver_.resolve(http_root, "http");
        resolver_.async_resolve(http_root, "http", std::bind(&HttpClient::handle_resolve, this
            , std::placeholders::_1, std::placeholders::_2));
    }
private:
    void handle_resolve(const boost::system::error_code &ec, const boost::asio::ip::tcp::resolver::results_type &endpoints)
    {
        if (ec) {
            SPDLOG_ERROR(ec.message());
        } else {
            boost::asio::async_connect(socket_, endpoints, std::bind(&HttpClient::handle_connect, this
                , std::placeholders::_1));
        }
    }

    void handle_connect(const boost::system::error_code &ec)
    {
        if (ec) {
            SPDLOG_ERROR(ec.message());
        } else {
            boost::asio::async_write(socket_, request_, std::bind(&HttpClient::handle_write_request, this
                , std::placeholders::_1, std::placeholders::_2));
        }
    }

    void handle_write_request(const boost::system::error_code &ec, std::size_t size)
    {
        if (ec) {
            SPDLOG_ERROR(ec.message());
        } else {
            boost::asio::async_read_until(socket_, response_, "\r\n", [this](const boost::system::error_code &ec, size_t size)
            {
                if (ec) {
                    SPDLOG_ERROR(ec.message());
                } else {
                    std::istream response_stream(&response_);
                    std::string http_version;
                    response_stream >> http_version;
                    unsigned int status_code;
                    response_stream >> status_code;
                    std::string status_message;
                    std::getline(response_stream, status_message);

                    using namespace std::literals::string_view_literals;
                    if (!response_stream || http_version.substr(0, 5) != "HTTP/"sv) {
                        spdlog::error("Invalid response");
                        return ;
                    }
                    if (status_code != 200) {
                        spdlog::error("Response return with status code {}, status messge : {}"
                            , status_code, status_message);
                        return ;
                    }

                    boost::asio::async_read_until(socket_, response_, "\r\n\r\n", std::bind(&HttpClient::handle_read_headers, this
                        , std::placeholders::_1, std::placeholders::_2));
                }
            });
        }
    }

    void handle_read_headers(const boost::system::error_code &ec, std::size_t size)
    {
        if (ec) {
            SPDLOG_ERROR(ec.message());
        } else {
            std::string header;
            std::istream response_stream(&response_);

            using namespace std::literals::string_view_literals;
            while (std::getline(response_stream, header) && header != "\r"sv) {
                spdlog::info(header);
            }

            if (response_.size() > 0) {
                std::cout << &response_;
            }

            boost::asio::async_read(socket_, response_, boost::asio::transfer_at_least(1)
                , std::bind(&HttpClient::handle_read_content, this
                    , std::placeholders::_1, std::placeholders::_2));
        }
    }

    void handle_read_content(const boost::system::error_code &ec, std::size_t size)
    {
        if (ec) {
            if (ec == boost::asio::error::eof) {
                std::cout << &response_;
            }
        } else {
            boost::asio::async_read(socket_, response_, boost::asio::transfer_at_least(1)
                , std::bind(&HttpClient::handle_read_content, this
                    , std::placeholders::_1, std::placeholders::_2));
        }
    }

private:
    boost::asio::io_context &io_context_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf request_;
    boost::asio::streambuf response_;
};

int main(int argc, char *argv[]) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %T.%e][%-5t][%^%l%$][%s.%!:%#] %v");

    using namespace std::literals::string_view_literals;
    //constexpr auto http_root = "127.0.0.1"sv;
    //constexpr auto http_path = "/root"sv;
    constexpr auto http_root = "cponline.cnipa.gov.cn"sv;
    constexpr auto http_path = "/"sv;

    try {
        boost::asio::io_context io_context;
        HttpClient client(io_context, http_root, http_path);
        io_context.run();
    } catch (const std::exception &e) {
        SPDLOG_ERROR(e.what());
    }

    return 0;
}
