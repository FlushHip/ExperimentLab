#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <ratio>

namespace hestina {

using timer_id = uint64_t;
using timer_callback_t = std::function<void()>;
using time_point = std::chrono::steady_clock::time_point;
using time_duration = std::chrono::microseconds;

class timer {
public:
    timer(timer_callback_t&& callback, time_point when, time_duration interval);
    ~timer();

    timer_id id() const { return id_; };
    bool repeat() const { return repeat_; };
    time_point when() const { return when_; };
    void run() const;
    void restart(time_point now);

    bool operator>(const timer& other) const { return when_ > other.when_; }
    static timer_id sinvalid_id;

private:
    timer_id id_;
    timer_callback_t callback_;
    time_point when_;
    time_duration interval_;
    bool repeat_;

    static std::atomic<timer_id> sbegin_id;
};

}  // namespace hestina
