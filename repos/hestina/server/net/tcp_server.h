#pragma once

#include "callback.h"

#include <memory>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_set>

namespace hestina {

class event_loop;
class channel;
class socket;
class acceptor;
class connection;
class tcp_server {
public:
    tcp_server(uint16_t port, std::string_view ip = "localhost");
    ~tcp_server();

    bool start();
    bool stop();

    void set_new_connection_callback(new_connection_callback_t&& callback);
    void set_data_arrive_callback(data_arrive_callback_t&& callback);
    void set_connection_close_callback(connection_close_callback_t&& callback);

private:
    void new_connection(std::unique_ptr<socket>&& sock);

    uint16_t port_;
    std::string ip_;

    std::unique_ptr<event_loop> event_loop_;
    std::thread thread_;

    std::unique_ptr<acceptor> acceptor_;
    std::unordered_set<std::shared_ptr<connection>> connections_;

    new_connection_callback_t new_connection_callback_;
    data_arrive_callback_t data_arrive_callback_;
    connection_close_callback_t connection_close_callback_;
};

}  // namespace hestina
