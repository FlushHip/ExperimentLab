#include <doctest/doctest.h>

#include <hestina/pool/thread_pool.h>
#include <hestina/util/mpsc_queue.hpp>

#include <algorithm>
#include <atomic>
#include <string>
#include <thread>

TEST_CASE("multiple productor single consumer queue") {
    hestina::util::mpsc_queue<std::string> que;

    int cnt = 100000;
    hestina::thread_pool tp;
    for (int i = 0; i < cnt; ++i) {
        tp.commit([&, i] { que.push(std::to_string(i)); });
    }

    std::vector<bool> used(cnt, false);
    hestina::work_thread wt;
    std::atomic_bool stop = false;
    auto fu = wt.commit([&] {
        std::string value;
        int result = 0;
        while (!stop) {
            if (que.pop(value)) {
                int i = std::stoi(value);
                REQUIRE(i >= 0);
                REQUIRE(i < cnt);
                used[i] = true;
                ++result;
            } else {
                std::this_thread::yield();
            }
        }
        return result;
    });

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    stop = true;

    CHECK(fu.get() == cnt);
    CHECK(std::all_of(
        used.begin(), used.end(), [](bool f) { return f == true; }));
}
