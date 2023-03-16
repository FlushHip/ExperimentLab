
#include <hestina/log/logger.h>
#include <hestina/net/buffer.h>
#include <hestina/net/connection.h>
#include <hestina/net/tcp_server.h>

#include <thread>

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::finer, true);

    hestina::tcp_server server(12345, "0.0.0.0");
    server.set_new_connection_callback(
        [](const std::weak_ptr<hestina::connection>& conn) {});
    server.set_data_arrive_callback(
        [](const std::weak_ptr<hestina::connection>& conn,
            hestina::buffer* buff) {
            if (!conn.expired()) {
                conn.lock()->send(buff->read());
            }
        });
    server.set_connection_close_callback(
        [](const std::weak_ptr<hestina::connection>& conn) {});
    server.start();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1h);
    return 0;
}
