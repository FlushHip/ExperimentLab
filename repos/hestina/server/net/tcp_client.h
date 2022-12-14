#pragma once

#include "callback.h"

#include <atomic>
#include <future>
#include <memory>

namespace hestina {

class socket;
class event_loop_thread;
class connection;
class connector;

class tcp_client {
public:
    tcp_client();
    ~tcp_client();

    bool connect(std::string_view ip, uint16_t port, bool async = true);

    void close();

    std::weak_ptr<connection> conn() const;

    void set_connection_establish_callback(
        connection_establish_callback_t&& callback);
    void set_data_arrive_callback(data_arrive_callback_t&& callback);
    void set_connection_close_callback(connection_close_callback_t&& callback);

private:
    void connect_fishsh(std::unique_ptr<socket>&& sock);
    void connect_close(std::weak_ptr<connection> conn);

    std::atomic_bool is_connect_{false};
    std::unique_ptr<event_loop_thread> loop_thread_;

    std::unique_ptr<std::promise<void>> promise_;

    std::unique_ptr<connector> connector_;
    std::shared_ptr<connection> connection_;

    connection_establish_callback_t connection_establish_callback_;
    data_arrive_callback_t data_arrive_callback_;
    connection_close_callback_t connection_close_callback_;
};
}  // namespace hestina
