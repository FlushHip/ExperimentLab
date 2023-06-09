#include <boost/system/error_code.hpp>
#include <exception>
#include <memory>
#include <thread>

#include <doctest/doctest.h>

#include "connection.hpp"
#include "logger.hpp"
#include "router.hpp"
#include "rpc_client.hpp"
#include "rpc_server.hpp"

TEST_CASE("test logger") {
    LOG_INFO << "hello rpc";
}

void fun_void(std::weak_ptr<rpc::detail::connection>,
    int i,
    std::string s,
    float f) {
    LOG_INFO << i << " " << s << " " << f;
}

int fun_int(std::weak_ptr<rpc::detail::connection>,
    int i,
    std::string s,
    float f) {
    LOG_INFO << i << " " << s << " " << f;
    return 1314;
}

TEST_CASE("test router") {
    rpc::detail::router router;
    router.rigister("flushhip_void", fun_void);
    router.rigister("flushhip_int", fun_int);
    router.rigister("lambda",
        [](std::weak_ptr<rpc::detail::connection>, int i, std::string s,
            float f) { LOG_INFO << "lambda"; });
    struct dummy {
        int fun(std::weak_ptr<rpc::detail::connection>,
            int i,
            std::string s,
            float f) {
            LOG_INFO << "member func";
        }
    } d;
    /*
    router.rigister("mem_fun",
        std::bind(&dummy::fun, &d, std::placeholders::_1, std::placeholders::_2,
            std::placeholders::_3));
            */

    router.route("flushhip_void");
    router.route("flushhip_int");
    router.route("lambda");
    router.route("mem_fun");
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
