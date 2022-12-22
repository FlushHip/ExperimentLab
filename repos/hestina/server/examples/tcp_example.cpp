#include <hestina/log/logger.h>
#include <hestina/net/connection.h>
#include <hestina/net/tcp_client.h>
#include <hestina/net/tcp_server.h>

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::finer, true);

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

    {
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
                if (!conn.expired()) {
                    conn.lock()->send(data);
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
    }

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1h);
    return 0;
}
