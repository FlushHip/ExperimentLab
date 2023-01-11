#pragma once

#include <functional>
#include <memory>

#include <hestina/net/callback.h>

namespace hestina {

class addr;
class socket;
class channel;
class event_loop;

class connector {
public:
    connector(event_loop* loop, std::string_view ip, uint16_t port);

    using connect_finish_callback_t =
        std::function<void(bool result, std::unique_ptr<socket>&&)>;
    void set_connect_finish_callback(connect_finish_callback_t&& callback);

    void connect();

private:
    void do_write();

    std::unique_ptr<addr> addr_;
    std::unique_ptr<socket> socket_;
    std::unique_ptr<channel> channel_;

    connect_finish_callback_t connect_finish_callback_;
};

}  // namespace hestina
