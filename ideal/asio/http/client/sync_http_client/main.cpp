#include <iostream>
#include <string_view>

#include <boost/asio.hpp>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>

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

        boost::asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(http_root, "http");

        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        boost::asio::streambuf request;
        std::ostream request_stream(&request);

        request_stream << "GET " << http_path << " HTTP/1.0\r\n";
        request_stream << "Host: " << http_root << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        boost::asio::write(socket, request);

        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/"sv) {
            spdlog::error("Invalid response");
            return 1;
        }
        if (status_code != 200) {
            spdlog::error("Response return with status code {}, status messge : {}"
                , status_code, status_message);
            return 1;
        }

        boost::asio::read_until(socket, response, "\r\n\r\n");

        std::string header;
        while (std::getline(response_stream, header) && header != "\r"sv) {
            spdlog::info(header);
        }

        if (response.size() > 0) {
            std::cout << &response;
        }

        boost::system::error_code ec;
        while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), ec)) {
            std::cout << &response;
        }
        if (ec != boost::asio::error::eof) {
            throw boost::system::system_error(ec);
        }

    } catch (std::exception &e) {
        spdlog::error(e.what());
    }

    return 0;
}
