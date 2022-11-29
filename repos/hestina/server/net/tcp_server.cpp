#include "tcp_server.h"

namespace hestina {

bool tcp_server::start() {
    if (!init()) {
        return false;
    }

    is_running_ = true;
    thread_ = std::thread([this] { run(); });
    return true;
}

bool tcp_server::stop() {
    is_running_ = false;
    if (thread_.joinable()) {
        thread_.join();
    }
    return true;
}

}  // namespace hestina
