#include "acceptor.h"

#include "addr.h"
#include "channel.h"
#include "socket.h"

namespace hestina {

acceptor::acceptor(event_loop* loop,
    uint16_t port,
    std::string_view ip,
    bool reuse_addr,
    bool reuse_port)
    : socket_(std::make_unique<socket>())
    , listen_channel_(std::make_unique<channel>(loop, socket_->fd())) {
    socket_->reuse_port(reuse_port);
    socket_->reuse_addr(reuse_addr);
    socket_->bind({ip, port});
    socket_->nonblocking();

    listen_channel_->set_read_event_callback([this] { do_read(); });
}

acceptor::~acceptor() = default;

void acceptor::set_new_connection_callback(
    new_connection_callback_t&& callback) {
    callback_ = std::move(callback);
}

void acceptor::listen() {
    socket_->listen();
    listen_channel_->enable_reading();
}

void acceptor::do_read() {
    addr addr;
    auto sock = std::make_unique<socket>(socket_->accept(addr));
    sock->nonblocking();
    if (callback_) {
        callback_(std::move(sock));
    }
}

}  // namespace hestina
