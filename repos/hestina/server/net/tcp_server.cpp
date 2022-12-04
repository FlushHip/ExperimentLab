#include "tcp_server.h"

#include "acceptor.h"
#include "addr.h"
#include "channel.h"
#include "event_loop.h"
#include "socket.h"

#include <iostream>

namespace hestina {
tcp_server::tcp_server(uint16_t port, std::string_view ip)
    : port_(port)
    , ip_(ip)
    , event_loop_(std::make_unique<event_loop>())
    , acceptor_(
          std::make_unique<acceptor>(event_loop_.get(), port, ip, true, true)) {
    acceptor_->set_new_connection_callback([this](auto&& sock) {
        new_connection(std::forward<decltype(sock)>(sock));
    });
    acceptor_->listen();
}

tcp_server::~tcp_server() = default;

bool tcp_server::start() {
    std::cerr << "server ip : " << ip_ << " port : " << port_ << " running..."
              << std::endl;
    thread_ = std::thread([this] { event_loop_->run(); });
    return true;
}
void tcp_server::new_connection(std::unique_ptr<socket>&& sock) {
    std::cerr << "new connection..." << std::endl;
    auto ch = std::make_unique<channel>(event_loop_.get(), sock->fd());
    ch->set_read_event_callback([this, sock = sock.get()] { do_read(sock); });
    ch->enable_reading();

    channels_.emplace(std::move(sock), std::move(ch));
}
void tcp_server::do_read(socket* sock) {
    constexpr int buff_length = 1024;
    char buff[buff_length + 1 + 4] = {0};
    while (true) {
        auto n = read(sock->fd(), buff, buff_length);
        if (n > 0) {
            buff[n] = '_';
            buff[n + 1] = 'd';
            buff[n + 2] = 'u';
            buff[n + 3] = 'p';
            buff[n + 4] = '\0';
            std::cerr << "recv : "
                      << std::string_view{buff,
                             static_cast<std::string_view::size_type>(n)}
                      << std::endl;
            write(sock->fd(), buff, n + 4);
        } else if (n == 0) {
            std::cerr << "recv : EOF" << std::endl;
            close(sock->fd());
            break;
        } else if (n == -1 && errno == EINTR) {
            std::cerr << "continue..." << std::endl;
            continue;
        } else if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            std::cerr << "finish once read" << std::endl;
            break;
        }
    }
}

bool tcp_server::stop() {
    if (thread_.joinable()) {
        thread_.join();
    }
    return true;
}

}  // namespace hestina
