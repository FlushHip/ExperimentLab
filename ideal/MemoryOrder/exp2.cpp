#include "main.h"

// int cnt{0};
std::atomic_int cnt{0};

void exp2() {
    std::vector<std::thread> threads(1000);
    for (auto &t : threads) {
        t = std::thread([&] {
            for (int i = 0; i < 10000; ++i) {
                // ++cnt;
                cnt.fetch_add(1, std::memory_order_relaxed);
            }
        });
    }
    for (auto &t : threads) {
        t.join();
    }
    std::cout << "cnt = " << cnt << std::endl;
}
