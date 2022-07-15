#include <exception>

#include <doctest/doctest.h>

#include "logger.hpp"
#include "rpc_client.hpp"

TEST_CASE("test logger") {
    LOG_INFO << "hello rpc";
}

int main(int argc, char** argv) {
    rpc::logger::init();

    try {
        rpc::client client("127.0.0.1", 10010);
        client.connect();
    } catch (std::exception& e) {
        LOG_ERROR << e.what();
    }

    return doctest::Context(argc, argv).run();
}
