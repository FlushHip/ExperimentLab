#include <boost/system/error_code.hpp>
#include <exception>
#include <thread>

#include <doctest/doctest.h>

#include "logger.hpp"
#include "rpc_client.hpp"
#include "rpc_server.hpp"

TEST_CASE("test logger") {
    LOG_INFO << "hello rpc";
}

TEST_CASE("run rpc client and server") {
    std::string ip{"127.0.0.1"};
    std::uint16_t port{10010};

    rpc::server server(ip, port);
    std::thread run_thread_server = std::thread([&] {
        try {
            server.run();
        } catch (const std::exception& e) {
            LOG_ERROR << e.what();
        }
    });

    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(1s);

    std::thread run_thread_client = std::thread([&] {
        try {
            rpc::client client(ip, port);
            CHECK(client.connect());
            client.async_call(
                "test",
                [](const boost::system::error_code& ec, std::string_view) {
                    LOG_INFO << ec.message();
                },
                1, 2, 3, 4, "flushhip", std::pair<int, std::string>{});
            std::this_thread::sleep_for(5s);
        } catch (const std::exception& e) {
            LOG_ERROR << e.what();
        }
    });

    run_thread_client.join();
    server.close();
    run_thread_server.join();
}

int main(int argc, char** argv) {
    rpc::logger::init();

    int result = doctest::Context(argc, argv).run();

    return result;
}
