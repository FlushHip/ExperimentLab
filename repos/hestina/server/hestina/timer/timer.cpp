#include "timer.h"
#include <chrono>

namespace hestina {

std::atomic<timer_id> timer::sbegin_id = 0;

timer::timer(timer_callback_t&& callback,
    time_point when,
    time_duration interval)
    : id_(++sbegin_id)
    , callback_(callback)
    , when_(when)
    , interval_(interval)
    , repeat_(interval.count() > 0) {}

timer::~timer() = default;

void timer::run() const {
    callback_();
}

void timer::restart(time_point now) {
    if (repeat_) {
        when_ = now + interval_;
    } else {
        when_ = std::chrono::steady_clock::now();
    }
}

}  // namespace hestina
