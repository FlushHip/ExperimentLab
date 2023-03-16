#include "main.h"

void exp1() {
    while (true) {
        std::atomic_int x{0}, y{0};
        int r1{0}, r2{0};
        auto thread1 = std::thread([&] {
            r1 = y.load(std::memory_order_relaxed); // A
            x.store(r1, std::memory_order_relaxed); // B
        });
        auto thread2 = std::thread([&]{
            r2 = x.load(std::memory_order_relaxed); // C
            y.store(42, std::memory_order_relaxed); // D
        });
        thread1.join();
        thread2.join();
        if (r1 == 42 && r2 == 42) {
            std::cerr << "OK" << std::endl;
        }
        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1ms);
    }
}
