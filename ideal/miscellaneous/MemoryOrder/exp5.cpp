#include "main.h"

namespace {
std::atomic<std::string *> ptr;
int data;
}

void exp5() {
    std::thread producer_t([&] {
        std::string *p = new std::string("Hello");
        data = 42;
        ptr.store(p, std::memory_order_release);
    });
    std::thread consumer_t([&] {
        std::string *p = nullptr;
        while ((p = ptr.load(std::memory_order_consume)) == nullptr) {
            std::this_thread::yield();
        }

        assert(*p == "Hello");
        assert(data == 42);
    });
    producer_t.join();
    consumer_t.join();
}
