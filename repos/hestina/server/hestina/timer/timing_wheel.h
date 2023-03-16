#pragma once

#include <hestina/timer/timer.h>

#include <atomic>
#include <deque>
#include <functional>
#include <limits>
#include <memory>
#include <unordered_set>
#include <vector>

namespace hestina {

class timer_queue;

class timing_wheel {
public:
    class callback_entry {
    public:
        callback_entry(std::function<void()>&& callback)
            : callback_(std::move(callback)) {}
        ~callback_entry() { callback_(); }

    private:
        std::function<void()> callback_;
    };

    timing_wheel(size_t wheels = 1,
        size_t interval = 1,  // ms
        size_t buckets_per_wheel = 100);
    ~timing_wheel();

    using entry_t = std::shared_ptr<void>;
    void insert(size_t delay,  // depend on interval
        entry_t entry);

private:
    std::unique_ptr<timer_queue> timer_queue_;
    timer_id timer_id_{0};

    size_t wheel_num_;
    size_t interval_;
    size_t buckets_per_wheel_;

    std::vector<std::deque<std::unordered_set<entry_t>>> wheels_;
    std::atomic_size_t ticks_{0};
};

}  // namespace hestina
