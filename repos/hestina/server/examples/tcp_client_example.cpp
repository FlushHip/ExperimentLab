
#include <hestina/log/logger.h>
#include <hestina/net/buffer.h>
#include <hestina/net/connection.h>
#include <hestina/net/tcp_client.h>

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::finer, true);

    hestina::tcp_client client;
    client.set_connection_establish_callback(
        [](const std::weak_ptr<hestina::connection>& conn) {
            if (!conn.expired()) {
                auto con = conn.lock();
                con->send("flushhip");
            }
        });
    client.set_data_arrive_callback(
        [](const std::weak_ptr<hestina::connection>& conn,
            hestina::buffer* buff) {
            if (!conn.expired()) {
                conn.lock()->send(buff->read());
            }
        });
    client.set_connection_close_callback(
        [](std::weak_ptr<hestina::connection> conn) {});

    bool res = client.connect("127.0.0.1", 12347, false);
    if (res) {
        client.conn().lock()->send("----------------");
    }
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10s);

    return 0;
}
