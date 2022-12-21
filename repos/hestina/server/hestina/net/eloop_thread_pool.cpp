#include "eloop_thread_pool.h"

#include "pool/thread_pool.h"

#include <future>

namespace hestina {

eloop_thread_pool::eloop_thread_pool(int nums)
    : loops_(nums), thread_pool_(std::make_unique<thread_pool>(nums)) {}

eloop_thread_pool::~eloop_thread_pool() {
    stop();
}

event_loop* eloop_thread_pool::get_eloop() {
    index_ %= loops_.size();
    return &loops_.at(index_++);
}

void eloop_thread_pool::start() {
    for (auto i = 0U; i < loops_.size(); ++i) {
        std::promise<void> pro;
        auto fu = pro.get_future();
        thread_pool_->commit([this, i, pro = std::move(pro)]() mutable {
            pro.set_value();
            loops_[i].run();
        });
        fu.wait();
    }
}

void eloop_thread_pool::stop() {
    for (auto i = 0U; i < loops_.size(); ++i) {
        loops_[i].stop();
    }
}

}  // namespace hestina
