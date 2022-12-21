#include "connector.h"

#include "log/logger.h"

#include "net/addr.h"
#include "net/channel.h"
#include "net/event_loop.h"
#include "net/socket.h"

#include <cerrno>
#include <cstring>

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
    // judege real connect to server : https://cr.yp.to/docs/connect.html
    if (auto addr = socket_->peer_addr(); addr != nullptr) {
        channel_->writing(false);
        channel_->reading(false);
        channel_->remove();

        if (connect_finish_callback_) {
            connect_finish_callback_(true, std::move(socket_));
        }
    } else if (errno == ENOTCONN) {
        char c{};
        socket_->read(&c, 1);
        log_warn << std::strerror(errno);
        if (connect_finish_callback_) {
            connect_finish_callback_(false, std::move(socket_));
        }
    } else {
        log_error << std::strerror(errno);
    }
}
}  // namespace hestina
