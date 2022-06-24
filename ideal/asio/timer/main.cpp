#include <iostream>

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#include <spdlog/spdlog.h>

void synchronous()
{
    spdlog::info(__LINE__);

    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
    t.wait();

    spdlog::info(__LINE__);
}

int main(int argc, char *argv[]) {
    synchronous();
    return 0;
}
