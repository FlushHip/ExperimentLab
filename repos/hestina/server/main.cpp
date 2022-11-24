#include <iostream>

#include "log/logger.h"
#include "pool/thread_pool.h"

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::trace);

    hestina::thread_pool pool;
    auto fn = [](int i) {
        for (int j = 0; j < 3; ++j) {
            log_trace << i << " cout " << j;
        }
    };
    for (int i = 0; i < 10; ++i) {
        auto fu = pool.commit(fn, i);
    }

    hestina::work_thread w_t;
    w_t.commit([&w_t] {
        log_debug << "................";
        w_t.commit([] { log_debug << "................"; });
    });

    return 0;
}
