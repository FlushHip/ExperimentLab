#include "websocket_server.h"

#include <memory>

#include <spdlog/fmt/bin_to_hex.h>
#include <boost/algorithm/hex.hpp>
#include <prettyprint.hpp>

#include "logger.hpp"
#include "sample_bus.h"

namespace hestina {
namespace detail {

websocket_server::websocket_server(std::string_view ip, std::string_view port)
    : ip_{ip}, port_{port} {
    sample_bus().connect([this](char* data, int len) { notify(data, len); });
}

void websocket_server::start() {
    server_.enable_timeout(false);
    server_.set_keep_alive_timeout(std::numeric_limits<long>::max());
    server_.listen(ip_, port_);

    std::string uri{"/usb_capture"};
    server_.set_http_handler<cinatra::GET, cinatra::POST>(uri,
        [this](cinatra::request& request, cinatra::response& /*response*/) {
            if (request.get_content_type() !=
                cinatra::content_type::websocket) {
                LOG_WARN << "someone use other protocol for websocket, type "
                            ": "
                         << static_cast<int>(request.get_content_type());
            }

            request.on(cinatra::ws_open, [this](cinatra::request& request) {
                ws_connect_handler(request);
            });

            request.on(cinatra::ws_message, [this](cinatra::request& request) {
                ws_message_handler(request);
            });

            request.on(cinatra::ws_close, [this](cinatra::request& request) {
                ws_close_handler(request);
            });

            request.on(cinatra::ws_error, [this](cinatra::request& request) {
                ws_error_handler(request);
            });
        });

    LOG_INFO << "start url ws://" << ip_ << ":" << port_ << uri;

    thread_ = std::make_unique<std::thread>([this] { main(); });
}

void websocket_server::stop() {
    LOG_INFO << "stop websocket server";
    server_.stop();
}

void websocket_server::ws_connect_handler(cinatra::request& request) {
    auto conn = request.get_conn<cinatra::NonSSL>();
    {
        std::lock_guard<std::mutex> lock(mutex_connections_);
        connections_.push_back(conn);
    }

    LOG_INFO << "websocket client " << conn->remote_ip_port() << " connect";
}

void websocket_server::ws_message_handler(cinatra::request& request) {
    LOG_INFO << "recv " << request.get_full_url()
             << " data : " << request.get_part_data();
}

void websocket_server::ws_close_handler(cinatra::request& request) {
    auto conn = request.get_conn<cinatra::NonSSL>();
    auto [ip, port] = conn->remote_ip_port();
    LOG_INFO << "websocket client " << conn->remote_ip_port() << " close";
}

void websocket_server::ws_error_handler(cinatra::request& request) {}

void websocket_server::main() {
    server_.run();
}

void websocket_server::notify(char* data, int len) {
    std::string str;
    boost::algorithm::hex(data, data + len, std::back_inserter(str));
    FMT_LOG_TRACE("raw data:{}", spdlog::to_hex(str));

    std::lock_guard<std::mutex> lock(mutex_connections_);
    for (auto& conn : connections_) {
        if (!conn.expired()) {
            conn.lock()->send_ws_string(str);
        }
    }
}

}  // namespace detail
}  // namespace hestina
