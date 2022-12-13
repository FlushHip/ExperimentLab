#include "log/logger.h"
#include "net/callback.h"
#include "net/connection.h"
#include "net/tcp_client.h"
#include "net/tcp_server.h"

#include <iostream>
#include <memory>
#include <string_view>
#include <thread>

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::finer, true);

    log_finer << "log.....";
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
            if (!conn.expired()) {
                conn.lock()->send(data);
            }
        });
    server.set_connection_close_callback(
        [](std::weak_ptr<hestina::connection> conn) {});
    server.start();

    hestina::tcp_client client;
    client.set_connection_establish_callback(
        [](std::weak_ptr<hestina::connection> conn) {
            if (!conn.expired()) {
                auto con = conn.lock();
                con->send("flushhip");
            }
        });
    client.set_data_arrive_callback(
        [](std::weak_ptr<hestina::connection> conn, std::string_view data) {
            log_info << "something recv";
            if (!conn.expired()) {
                // conn.lock()->send(data);
            }
        });
    client.set_connection_close_callback(
        [](std::weak_ptr<hestina::connection> conn) {
            log_info << "connection close";
        });

    client.connect("127.0.0.1", 12346);

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1h);

    return 0;
}
