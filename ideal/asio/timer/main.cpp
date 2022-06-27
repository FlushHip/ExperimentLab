#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

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


void printA(const boost::system::error_code &, const boost::asio::strand<boost::asio::io_context::executor_type> &strand, boost::asio::steady_timer *t, int *cnt)
{
    if (*cnt < 6) {
        SPDLOG_DEBUG("cnt is {}", *cnt);
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        ++*cnt;
        t->async_wait(boost::asio::bind_executor(strand, std::bind(printA, std::placeholders::_1, strand, t, cnt)));

        return;
    }
    SPDLOG_DEBUG("finish");
}

void printB(const boost::system::error_code &, const boost::asio::strand<boost::asio::io_context::executor_type> &strand, boost::asio::steady_timer *t, int *cnt)
{
    if (*cnt < 6) {
        SPDLOG_DEBUG("cnt is {}", *cnt);
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        ++*cnt;
        t->async_wait(boost::asio::bind_executor(strand, std::bind(printB, std::placeholders::_1, strand, t, cnt)));

        return;
    }
    SPDLOG_DEBUG("finish");
}

void asynchronous()
{
    SPDLOG_DEBUG("start");
    boost::asio::io_context io;
    auto strand = boost::asio::make_strand(io);
    boost::asio::steady_timer tA(io, boost::asio::chrono::seconds(1));
    boost::asio::steady_timer tB(io, boost::asio::chrono::seconds(1));
    int cnt = 0;

    tA.async_wait(boost::asio::bind_executor(strand, std::bind(printA, std::placeholders::_1, strand, &tA, &cnt)));
    tB.async_wait(boost::asio::bind_executor(strand, std::bind(printB, std::placeholders::_1, strand, &tB, &cnt)));

    boost::asio::thread_pool pool(4);
    for (int i = 0; i < 4; ++i) {
        boost::asio::post(pool, [&io] { io.run(); });
    }
    pool.join();

    SPDLOG_DEBUG("final cnt is {}", cnt);

    SPDLOG_DEBUG("end");
}

int main(int argc, char *argv[]) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %T.%e][%-5t][%^%l%$][%s.%!:%#] %v");

    synchronous();
    asynchronous();

    return 0;
}
