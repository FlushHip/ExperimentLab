#include "log/logger.h"
#include "net/tcp_server.h"

#include <iostream>
#include <thread>

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::trace);

    hestina::tcp_server server(12345, "0.0.0.0");
    server.start();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1h);

    return 0;
}
