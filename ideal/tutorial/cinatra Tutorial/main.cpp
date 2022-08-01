#include <cinatra.hpp>
#include <thread>
using namespace cinatra;

int main() {
    http_server server(std::thread::hardware_concurrency());
    server.listen("127.0.0.1", "8080");

    // web socket
    server.set_http_handler<GET, POST>("/ws", [](request& req, response& res) {
        assert(req.get_content_type() == content_type::websocket);

        req.on(ws_open,
            [](request& req) { std::cout << "websocket start" << std::endl; });

        req.on(ws_message, [](request& req) {
            auto part_data = req.get_part_data();
            // echo
            std::string str = std::string(part_data.data(), part_data.length());
            req.get_conn<cinatra::NonSSL>()->send_ws_string(std::move(str));
            std::cout << part_data.data() << std::endl;
        });

        req.on(ws_error, [](request& req) {
            std::cout << "websocket pack error or network error" << std::endl;
        });
    });

    std::make_unique<std::thread>([&server] { server.run(); })->join();
    return 0;
}
