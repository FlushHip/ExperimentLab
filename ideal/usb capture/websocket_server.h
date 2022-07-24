#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include <cinatra/connection.hpp>
#include <cinatra/http_server.hpp>
#include "cinatra/request.hpp"

#include "thread_controller.hpp"

namespace hestina {
namespace detail {

class websocket_server : public thread_controller {
public:
    websocket_server(std::string_view ip, std::string_view port);

    void start() override;

private:
    void main();
    void notify(char* data, int len);

    void ws_connect_handler(cinatra::request& request);
    void ws_message_handler(cinatra::request& request);
    void ws_close_handler(cinatra::request& request);
    void ws_error_handler(cinatra::request& request);

private:
    std::string ip_;
    std::string port_;

    cinatra::http_server server_{std::thread::hardware_concurrency()};

    std::mutex mutex_connections_;
    std::vector<std::weak_ptr<cinatra::connection<cinatra::NonSSL>>>
        connections_;
};

}  // namespace detail
}  // namespace hestina
