#pragma once

#include "callback.h"

#include <memory>

namespace hestina {

class channel;
class socket;
class event_loop;
class buffer;
class addr;

class connection : public std::enable_shared_from_this<connection> {
public:
    enum class status_t {
        connecting,
        connected,
        disconnecting,
        disconnected,
    };

    connection(event_loop* loop, std::unique_ptr<socket>&& sock);
    ~connection();

    status_t status() const;

    void send(std::string_view data);

    const addr& local_addr() const;
    const addr& peer_addr() const;

private:
    friend class tcp_server;
    friend class tcp_client;

    void established();
    void closed();

    void set_connection_establish_callback(
        const connection_establish_callback_t& callback);
    void set_data_arrive_callback(const data_arrive_callback_t& callback);
    void set_connection_close_callback(
        const connection_close_callback_t& callback);

    void do_read();
    void do_close();
    void do_error();

    void read_finished();

    std::unique_ptr<socket> socket_;
    std::unique_ptr<channel> channel_;

    std::unique_ptr<addr> local_addr_, peer_addr_;

    connection_establish_callback_t new_connection_callback_;
    data_arrive_callback_t data_arrive_callback_;
    connection_close_callback_t connection_close_callback_;

    std::unique_ptr<buffer> buffer_;

    status_t status_{status_t::connecting};
};

}  // namespace hestina
