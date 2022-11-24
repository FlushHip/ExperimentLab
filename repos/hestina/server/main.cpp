#include <iostream>

#include "log/logger.h"

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::trace);

    for (int i = 0; i < 10; ++i) {
        log_trace << "logger " << i * 10;
        log_debug << "logger " << i * 11;
        log_info << "logger " << i * 12;
        log_warn << "logger " << i * 13;
        log_fatal << "logger " << i * 14;
    }

    return 0;
}
