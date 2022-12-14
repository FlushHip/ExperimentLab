#include "connector.h"

#include "log/logger.h"
#include "net/addr.h"
#include "net/channel.h"
#include "net/event_loop.h"
#include "net/socket.h"

namespace hestina {

connector::connector(event_loop* loop, std::string_view ip, uint16_t port)
    : addr_(std::make_unique<addr>(ip, port))
    , socket_(std::make_unique<socket>())
    , channel_(std::make_unique<channel>(loop, socket_->fd())) {
    socket_->nonblocking();

    channel_->set_write_event_callback([this] { do_write(); });
}

void connector::set_connect_finish_callback(
    connect_finish_callback_t&& callback) {
    connect_finish_callback_ = std::move(callback);
}

void connector::connect() {
    int ret = socket_->connect(*addr_);
    channel_->et();
    channel_->writing();
}

void connector::do_write() {
    channel_->writing(false);
    channel_->reading(false);
    channel_->remove();

    if (connect_finish_callback_) {
        connect_finish_callback_(std::move(socket_));
    }
}
}  // namespace hestina
