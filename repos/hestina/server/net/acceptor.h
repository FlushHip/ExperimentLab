#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string_view>
#include "event_loop.h"

namespace hestina {

class socket;
class channel;
class event_loop;

class acceptor {
public:
    acceptor(event_loop* loop,
        uint16_t port,
        std::string_view ip,
        bool reuse_addr = true,
        bool reuse_port = true);
    ~acceptor();

    using new_connection_callback_t =
        std::function<void(std::unique_ptr<socket>&&)>;
    void set_new_connection_callback(new_connection_callback_t&& callback);
    void listen();

private:
    void do_read();

    std::unique_ptr<socket> socket_;
    std::unique_ptr<channel> listen_channel_;
    new_connection_callback_t callback_;
};

}  // namespace hestina
