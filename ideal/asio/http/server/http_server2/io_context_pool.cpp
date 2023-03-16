#pragma once

#include "io_context_pool.hpp"

namespace http {
namespace server {

IoContextPool::IoContextPool()
    : next_context(0u)
    , contexts_(std::thread::hardware_concurrency())
{
    for (auto i = 0u; i < contexts_.size(); ++i) {
        contexts_[i].guard = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>
            (boost::asio::make_work_guard(contexts_[i].io_context));
    }
}

void IoContextPool::run()
{
    for (auto i = 0u; i < contexts_.size(); ++i) {
        contexts_[i].thread = std::thread([i, this] {
            contexts_[i].io_context.run();
        });
    }
    for (auto i = 0u; i < contexts_.size(); ++i) {
        contexts_[i].thread.join();
    }
}

void IoContextPool::stop()
{
    for (auto i = 0u; i < contexts_.size(); ++i) {
        contexts_[i].io_context.stop();
    }
}

boost::asio::io_context& IoContextPool::io_context()
{
    if (next_context == contexts_.size()) {
        next_context = 0u;
    }
    return contexts_[next_context++].io_context;
}

}
}
