#include <exception>
#include "logger.hpp"
#include "rpc_client.hpp"

int main(int /*argc*/, char** /*argv*/) {
    rpc::logger::init();

    LOG_INFO << "hello rpc";

    try {
        rpc::client client("127.0.0.1", 10010);
        client.connect();
    } catch (std::exception& e) {
        LOG_ERROR << e.what();
    }
    return 0;
}
