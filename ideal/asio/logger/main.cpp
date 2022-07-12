#include <exception>
#include <iostream>

#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <sstream>

#include "logger.hpp"

template <typename Buffer>
void do_read(boost::asio::ip::tcp::socket& socket, Buffer& buffer) {
    socket.async_read_some(boost::asio::buffer(buffer),
        [&socket, &buffer](
            const boost::system::error_code& ec, size_t bytes_transferred) {
            services::logger logger(boost::asio::query(socket.get_executor(),
                                        boost::asio::execution::context),
                "do_read");
            if (!ec) {
                logger.log(std::string(buffer.data(), bytes_transferred));

                do_read(socket, buffer);
            } else {
                logger.log(ec.message());
            }
        });
}

int main(int /*argc*/, char* /*argv*/[]) {
    try {
        boost::asio::io_context io_context(1);
        boost::asio::ip::tcp::resolver resolver(io_context);
        using namespace std::literals::string_view_literals;
        boost::asio::ip::tcp::endpoint endpoint =
            *resolver.resolve("time.nist.gov"sv, "daytime"sv).begin();

        services::logger logger(io_context, "");
        logger.use_file("log.txt");

        std::stringstream ss;
        ss << endpoint.address().to_string() << " : " << endpoint.port()
           << std::endl;
        logger.log(ss.str());

        boost::asio::ip::tcp::socket socket(io_context);
        std::array<char, 1024> buffer = {0};
        socket.async_connect(
            endpoint, [&socket, &buffer](const boost::system::error_code& ec) {
                services::logger logger(
                    boost::asio::query(
                        socket.get_executor(), boost::asio::execution::context),
                    "connect lambda");
                if (!ec) {
                    logger.log("Connection established");
                    do_read(socket, buffer);
                } else {
                    logger.log(ec.message());
                }
            });

        io_context.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
