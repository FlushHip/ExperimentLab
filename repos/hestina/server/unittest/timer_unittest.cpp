#include <doctest/doctest.h>

#include "log/logger.h"
#include "timer/timer_queue.h"

#include <chrono>
#include <thread>

TEST_CASE("timer queue") {
    hestina::timer_queue tq;
    int value = 0;
    using namespace std::chrono_literals;
    auto idx = tq.add_timer([&value]() mutable { ++value; },
        std::chrono::steady_clock::now() + 1s, 1s);
    int top = 5;
    for (int i = 0; i < top; ++i) {
        CHECK(value == i);
        std::this_thread::sleep_for(1.1s);
        CHECK(value == i + 1);
    }
    tq.remove_timer(idx);
    std::this_thread::sleep_for(1.1s);
    CHECK(value == top);
    std::this_thread::sleep_for(1.1s);
    CHECK(value == top);

    log_info << "finish";
}
