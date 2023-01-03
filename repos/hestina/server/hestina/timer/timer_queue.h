#pragma once

#include <hestina/timer/timer.h>

#include <memory>
#include <queue>
#include <unordered_set>

namespace hestina {

class event_loop_thread;
class channel;

class timer_queue {
public:
    timer_queue();
    ~timer_queue();

    timer_id add_timer(timer_callback_t&& callback,
        time_point when,
        time_duration interval = time_duration{});

    void remove_timer(timer_id id);

private:
    bool insert_timer(std::shared_ptr<timer> ptr);
    void reset_timer(const std::vector<std::shared_ptr<timer>>& timers,
        time_point point);
    void settime(time_point point);
    void do_read();
    void do_run(const std::vector<std::shared_ptr<timer>>& timers);
    std::vector<std::shared_ptr<timer>> expired(time_point point);

    std::unique_ptr<event_loop_thread> loop_thread_;
    int fd_;
    std::unique_ptr<channel> channel_;

    struct cmp {
        bool operator()(const std::shared_ptr<timer>& lhs,
            const std::shared_ptr<timer>& rhs) {
            return *lhs > *rhs;
        }
    };
    std::priority_queue<std::shared_ptr<timer>,
        std::vector<std::shared_ptr<timer>>,
        cmp>
        timers_;
    std::unordered_set<timer_id> ids_;
};

}  // namespace hestina
