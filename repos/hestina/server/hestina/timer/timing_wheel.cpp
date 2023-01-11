#include "timing_wheel.h"

#include <hestina/timer/timer_queue.h>

#include <chrono>
#include <memory>
#include <unordered_set>

namespace hestina {

timing_wheel::timing_wheel(size_t wheels,
    size_t interval,
    size_t buckets_per_wheel)
    : timer_queue_(std::make_unique<timer_queue>())
    , wheel_num_(wheels)
    , interval_(interval)
    , buckets_per_wheel_(buckets_per_wheel)
    , wheels_(wheels,
          std::deque<std::unordered_set<entry_t>>(buckets_per_wheel)) {
    double i = 0;
    timer_id_ = timer_queue_->add_timer(
        [this] {
            ++ticks_;
            auto t = ticks_.load();
            size_t power = 1;
            for (int i = 0; i < wheel_num_; ++i) {
                if (t % power == 0) {
                    wheels_[i].pop_front();
                    wheels_[i].emplace_back();
                }
                power *= buckets_per_wheel_;
            }
        },
        std::chrono::steady_clock::now() + std::chrono::milliseconds(interval_),
        std::chrono::milliseconds(interval_));
}

timing_wheel::~timing_wheel() {
    timer_queue_->remove_timer(timer_id_);
};

void timing_wheel::insert(size_t delay, entry_t entry) {
    auto t = ticks_.load();
    for (int i = 0; i < wheel_num_; ++i) {
        if (delay <= buckets_per_wheel_) {
            wheels_[i][delay - 1].insert(entry);
            break;
        }
        if (i != wheel_num_ - 1) {
            entry =
                std::make_shared<callback_entry>([t, delay, i, entry, this] {
                    wheels_[i][((t % buckets_per_wheel_) + delay - 1) %
                        buckets_per_wheel_]
                        .insert(entry);
                });
        } else {
            wheels_[wheel_num_ - 1][buckets_per_wheel_ - 1].insert(entry);
        }

        delay = ((t % buckets_per_wheel_) + delay - 1) / buckets_per_wheel_;
        t /= buckets_per_wheel_;
    }
}

}  // namespace hestina
