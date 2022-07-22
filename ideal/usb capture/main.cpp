#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <string_view>
#include <thread>

#include <boost/algorithm/hex.hpp>

#include <cinatra/define.h>
#include <cinatra/connection.hpp>
#include <cinatra/http_server.hpp>
#include <cinatra/request.hpp>
#include <cinatra/response.hpp>

#include <prettyprint.hpp>

#include <spdlog/fmt/bin_to_hex.h>

#include "logger.hpp"
#include "usb_cap/usb_cap.h"

std::vector<std::weak_ptr<cinatra::connection<cinatra::NonSSL>>> connections;

void handle_capture(char* data, int len) {
    std::string str;
    boost::algorithm::hex(data, data + len, std::back_inserter(str));
    FMT_LOG_TRACE("raw data:{}", spdlog::to_hex(str));
    for (auto& conn : connections) {
        if (!conn.expired()) {
            conn.lock()->send_ws_string(str);
        }
    }
}

void do_websocket_server() {
    cinatra::http_server server(std::thread::hardware_concurrency());
    server.enable_timeout(false);
    server.set_keep_alive_timeout(std::numeric_limits<long>::max());
    server.listen("0.0.0.0", "8081");

    server.set_http_handler<cinatra::GET, cinatra::POST>("/usb_capture",
        [](cinatra::request& request, cinatra::response& /*response*/) {
            // assert(
            //     request.get_content_type() ==
            //     cinatra::content_type::websocket);
            if (request.get_content_type() !=
                cinatra::content_type::websocket) {
                LOG_WARN << "someone use other protocol for websocket, type : "
                         << static_cast<int>(request.get_content_type());
            }

            request.on(cinatra::ws_open, [](cinatra::request& request) {
                auto conn = request.get_conn<cinatra::NonSSL>();
                connections.push_back(conn);

                auto [ip, port] = conn->remote_ip_port();
                LOG_INFO << "websocket client ip : " << ip
                         << ", port : " << port << " connect";
            });

            request.on(cinatra::ws_message, [](cinatra::request& request) {
                LOG_INFO << "recv " << request.get_full_url()
                         << " data : " << request.get_part_data();
            });

            request.on(cinatra::ws_close, [](cinatra::request& request) {});

            request.on(cinatra::ws_error, [](cinatra::request& request) {
                LOG_ERROR << request.get_full_url() << " some error : "
                          << request.get_conn<cinatra::NonSSL>()
                                 ->get_res()
                                 .raw_content();
            });
        });

    server.run();
}

void do_usb_capture() {
    Init();
    if (SetFilter(1) < 0) {
        LOG_ERROR << "set filter fail" << std::endl;
        return;
    }
    LOG_INFO << "start usb capture";
    StartCapture(handle_capture);
    LOG_INFO << "end usb capture";
}

int main(int argc, char** argv) {
    detail::logger::init();

    LOG_INFO << argv[0] << " start.";

    std::vector<std::shared_ptr<std::thread>> threads{
        std::make_shared<std::thread>(do_usb_capture),
        std::make_shared<std::thread>(do_websocket_server),
    };

    for (int i = 0; i < threads.size(); ++i) {
        if (threads[i]->joinable()) {
            threads[i]->join();
        }
    }
    return 0;
}
