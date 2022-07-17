#include <exception>
#include <thread>

#include <doctest/doctest.h>

#include "logger.hpp"
#include "rpc_client.hpp"

TEST_CASE("test logger") {
    LOG_INFO << "hello rpc";
}

TEST_CASE("run rpc client") {
    std::thread run_thread = std::thread([] {
        try {
            rpc::client client("127.0.0.1", 10010);
            CHECK(client.connect());
        } catch (const std::exception& e) {
            LOG_ERROR << e.what();
        }
    });

    run_thread.join();
}

int main(int argc, char** argv) {
    rpc::logger::init();

    int result = doctest::Context(argc, argv).run();

    return result;
}
