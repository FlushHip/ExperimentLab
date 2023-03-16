#pragma once

#include <hestina/net/callback.h>

#include <memory>
#include <string>
#include <string_view>
#include <unordered_set>

namespace hestina {

class event_loop;
class channel;
class socket;
class acceptor;
class connection;
class event_loop_thread;
class eloop_thread_pool;
class timer_queue;
class tcp_server {
public:
    tcp_server(uint16_t port, std::string_view ip = "localhost");
    ~tcp_server();

    bool start();
    bool stop();

    void set_new_connection_callback(
        connection_establish_callback_t&& callback);
    void set_data_arrive_callback(data_arrive_callback_t&& callback);
    void set_connection_close_callback(connection_close_callback_t&& callback);

    // seconds
    void off_idle_connections(size_t timeout);

private:
    void new_connection(std::unique_ptr<socket>&& sock);
    void connection_close(std::weak_ptr<connection>&& conn);

    uint16_t port_;
    std::string ip_;

    std::unique_ptr<event_loop_thread> main_loop_thread_;
    std::unique_ptr<eloop_thread_pool> sub_loop_thread_pool_;

    std::unique_ptr<acceptor> acceptor_;
    std::unordered_set<std::shared_ptr<connection>> connections_;

    connection_establish_callback_t new_connection_callback_;
    data_arrive_callback_t data_arrive_callback_;
    connection_close_callback_t connection_close_callback_;

    size_t idle_timeout_{0};
    std::unique_ptr<timer_queue> idle_timer_;
};

}  // namespace hestina
