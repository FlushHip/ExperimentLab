#include <iostream>

#include <boost/asio.hpp>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>

void synchronous()
{
    SPDLOG_DEBUG("start");

    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(2));
    t.wait();

    SPDLOG_TRACE("end");
}

void asynchronous()
{
    SPDLOG_DEBUG("start");
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(2));
    t.async_wait([](const boost::system::error_code &)
    {
        SPDLOG_DEBUG("finish");
    });

    io.run();
    SPDLOG_DEBUG("end");
}

int main(int argc, char *argv[]) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %T] [%t] [%^%l%$] [%s:%#][%!] %v");

    synchronous();
    asynchronous();

    return 0;
}
