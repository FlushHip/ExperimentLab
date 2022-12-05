#pragma once

#include "callback.h"

#include <memory>

namespace hestina {

class channel;
class socket;
class event_loop;
class buffer;

class connection : public std::enable_shared_from_this<connection> {
public:
    connection(event_loop* loop, std::unique_ptr<socket>&& sock);
    ~connection();

    void established();

    void set_new_connection_callback(const new_connection_callback_t& callback);
    void set_data_arrive_callback(const data_arrive_callback_t& callback);
    void set_connection_close_callback(
        const connection_close_callback_t& callback);

    void send(std::string_view data);

private:
    void do_read();
    void do_close();
    void do_error();

    std::unique_ptr<socket> socket_;
    std::unique_ptr<channel> channel_;

    new_connection_callback_t new_connection_callback_;
    data_arrive_callback_t data_arrive_callback_;
    connection_close_callback_t connection_close_callback_;

    std::unique_ptr<buffer> buffer_;
};

}  // namespace hestina
