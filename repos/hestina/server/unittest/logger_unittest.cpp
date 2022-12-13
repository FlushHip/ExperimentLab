#include <doctest/doctest.h>

#include "log/logger.h"

#include <thread>

TEST_CASE("logger level print") {
    using namespace std::chrono_literals;

    std::this_thread::sleep_for(1ms);

    log_finer << "log.....";
    log_trace << "log.....";
    log_debug << "log.....";
    log_info << "log.....";
    log_warn << "log.....";
    log_error << "log.....";
    log_fatal << "log.....";

    std::this_thread::sleep_for(1ms);
}
