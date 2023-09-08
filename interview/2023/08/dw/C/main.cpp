#include <atomic>
#include <iostream>
#include <thread>

#include <dbg.h>

int main() {
    std::atomic_int i = 0;
    auto fn = [&] {
        for (int L = 0; L < 5000; ++L) {
            ++i;
            dbg(i);
        }
    };
    std::thread t1(fn);
    std::thread t2(fn);

    t1.join();
    t2.join();

    std::cout << i << std::endl;

    return 0;
}