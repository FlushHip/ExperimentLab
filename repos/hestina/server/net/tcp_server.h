#pragma once

#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>

namespace hestina {

class event_loop;
class channel;
class socket;
class acceptor;
class tcp_server {
public:
    tcp_server(uint16_t port, std::string_view ip = "localhost");
    ~tcp_server();

    bool start();
    bool stop();

private:
    void new_connection(std::unique_ptr<socket>&& sock);
    void do_read(socket* sock);

    uint16_t port_;
    std::string ip_;

    std::unique_ptr<event_loop> event_loop_;
    std::thread thread_;

    std::unique_ptr<acceptor> acceptor_;
    std::unordered_map<std::unique_ptr<socket>, std::unique_ptr<channel>>
        channels_;
};
}  // namespace hestina
