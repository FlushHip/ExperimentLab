#include "main.h"

namespace {
std::vector<int> data;
std::atomic_int flag;
}

void exp4() {
    std::thread a([&] {
        data.push_back(42);
        flag.store(1, std::memory_order_release);
    });
    std::thread b([&] {
        int expected = 1;
        while (!flag.compare_exchange_strong(expected, 2, std::memory_order_acquire)) {
            expected = 1;
        }
    });
    std::thread c([&] {
        while (flag.load(std::memory_order_acquire) != 2) {
            std::this_thread::yield();
        }
        assert(data.size() == 1 && data.at(0) == 42);
    });
    a.join();
    b.join();
    c.join();
}
