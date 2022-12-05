#pragma once

#include "event_loop.h"

#include <memory>
#include <vector>

namespace hestina {

class thread_pool;

class eloop_thread_pool {
public:
    eloop_thread_pool(int nums);
    ~eloop_thread_pool();

    void start();

    event_loop* get_eloop();

private:
    size_t index_{0U};
    std::vector<event_loop> loops_;
    std::unique_ptr<thread_pool> thread_pool_;
};

class event_loop_thread : public eloop_thread_pool {
public:
    event_loop_thread() : eloop_thread_pool(1) {}
};

}  // namespace hestina
