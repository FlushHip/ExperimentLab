#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <string_view>
#include <thread>

#include <boost/algorithm/hex.hpp>
#include <boost/process.hpp>

#include <cinatra/define.h>
#include <cinatra/connection.hpp>
#include <cinatra/http_server.hpp>
#include <cinatra/request.hpp>
#include <cinatra/response.hpp>

#include <argagg/argagg.hpp>
#include <prettyprint.hpp>

#include <spdlog/fmt/bin_to_hex.h>

#include "logger.hpp"
#include "usb_cap/usb_cap.h"
#include "utils.h"

namespace {

std::string ip = "127.0.0.1";
std::string port = "28168";
int filter = 1;
bool is_service = false;

std::mutex mutex_connections;
std::vector<std::weak_ptr<cinatra::connection<cinatra::NonSSL>>> connections;

}  // namespace

void handle_capture(char* data, int len) {
    std::string str;
    boost::algorithm::hex(data, data + len, std::back_inserter(str));
    FMT_LOG_TRACE("raw data:{}", spdlog::to_hex(str));

    std::lock_guard<std::mutex> lock(mutex_connections);
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
    server.listen(ip, port);

    server.set_http_handler<cinatra::GET, cinatra::POST>("/usb_capture",
        [](cinatra::request& request, cinatra::response& /*response*/) {
            if (request.get_content_type() !=
                cinatra::content_type::websocket) {
                LOG_WARN << "someone use other protocol for websocket, type : "
                         << static_cast<int>(request.get_content_type());
            }

            request.on(cinatra::ws_open, [](cinatra::request& request) {
                auto conn = request.get_conn<cinatra::NonSSL>();
                {
                    std::lock_guard<std::mutex> lock(mutex_connections);
                    connections.push_back(conn);
                }

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

    LOG_INFO << "websocket server start, ip : " << ip << ", port : " << port;

    server.run();
}

void do_usb_capture() {
    Init();
    if (SetFilter(filter) < 0) {
        LOG_ERROR << "set filter fail" << std::endl;
        return;
    }
    LOG_INFO << "start usb capture";
    StartCapture(handle_capture);
    LOG_INFO << "end usb capture";
}

int rigister_service() {
    auto result = tool::rigister_service();
    (result == 0 ? LOG_INFO : LOG_ERROR)
        << "resister service " << (result == 0 ? "success" : "fail");
    return result;
}

int unrigister_service() {
    auto result = tool::unrigister_service();
    (result == 0 ? LOG_INFO : LOG_ERROR)
        << "unresister service " << (result == 0 ? "success" : "fail");
    return result;
}

int init_options(int argc, char** argv) {
    argagg::parser argparser{{
        {"help", {"-h", "--help"}, "shows this help message", 0},
        {"rigister", {"-r", "--rigister"}, "register windows service", 0},
        {"unrigister", {"-u", "--unrigister"}, "unregister windows service", 0},
        {"ip", {"-i", "--ip"}, "ip[x.x.x.x], default: " + ip, 1},
        {"port", {"-p", "--port"}, "port, default: " + port, 1},
        {"filter", {"-f", "--filter"}, "USBCap filter", 1},
        {"service", {"-s", "--service"},
            "run as service(only for sc, don't use this option in dos cmd)", 0},
    }};
    argagg::parser_results args;
    try {
        args = argparser.parse(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }
    if (args["help"]) {
        std::cerr << "Usage: " << tool::process_name() << " [options]"
                  << std::endl
                  << argparser;
        return 0;
    }
    if (args["rigister"]) {
        return rigister_service();
    }
    if (args["unrigister"]) {
        return unrigister_service();
    }
    if (args["ip"]) {
        ip = args["ip"].as<std::string>();
    }
    if (args["port"]) {
        port = args["port"].as<std::string>();
    }
    if (args["filter"]) {
        filter = args["filter"].as<int>();
    }
    if (args["service"]) {
        is_service = true;
    }
    return 1;
}

int common_main() {
    LOG_INFO << tool::process_name() << " start. ---------";

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

int main(int argc, char** argv) {
    detail::logger::init();

    int result = init_options(argc, argv);
    if (result == 0 || result == -1) {
        return 0;
    }

    if (is_service) {
        LOG_INFO << "run as service";
        tool::run_service(common_main);
    } else {
        LOG_INFO << "run as normal process";
        common_main();
    }

    return 0;
}
