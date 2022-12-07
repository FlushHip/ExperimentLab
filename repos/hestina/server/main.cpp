#include "log/logger.h"
#include "net/callback.h"
#include "net/connection.h"
#include "net/tcp_server.h"

#include <iostream>
#include <memory>
#include <thread>

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::trace, true);

    log_trace << "log.....";
    log_debug << "log.....";
    log_info << "log.....";
    log_warn << "log.....";
    log_error << "log.....";
    log_fatal << "log.....";

    hestina::tcp_server server(12345, "0.0.0.0");
    server.set_new_connection_callback(
        [](std::weak_ptr<hestina::connection> conn) {});
    server.set_data_arrive_callback(
        [](std::weak_ptr<hestina::connection> conn, std::string_view data) {
            // if (!conn.expired()) {
            //     conn.lock()->send(data);
            // }
        });
    server.set_connection_close_callback(
        [](std::weak_ptr<hestina::connection> conn) {});
    server.start();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1h);

    return 0;
}
