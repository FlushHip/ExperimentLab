#include <iostream>
#include <string_view>

#include <spdlog/spdlog.h>

#include "server.hpp"

int main(int argc, char *argv[]) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %T.%e][%-5t][%^%l%$][%s.%!:%#] %v");

    using namespace std::literals::string_view_literals;
    constexpr auto address = "127.0.0.1"sv;
    constexpr auto port = "80"sv;
    constexpr auto doc_root = R"(D:\)"sv;

    try {
        http::server::HttpServer server(address, port, doc_root);
        server.run();
    } catch (const std::exception &e) {
        spdlog::error(e.what());
    }

    return 0;
}
