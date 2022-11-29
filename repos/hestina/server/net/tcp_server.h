#pragma once

#include <atomic>
#include <string>
#include <string_view>
#include <thread>

namespace hestina {
class tcp_server {
public:
    tcp_server(uint16_t port, std::string_view ip = "localhost");

    bool start();
    bool stop();

private:
    bool init();
    void run();

    uint16_t port_;
    std::string ip_;

    std::atomic_bool is_running_{false};
    std::thread thread_;
};
}  // namespace hestina
