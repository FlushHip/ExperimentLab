#pragma once

#include <boost/asio/io_context.hpp>

namespace rpc {
namespace detail {

class io_context_pool {
public:
    io_context_pool() : contexts_(std::thread::hardware_concurrency()) {
        for (auto i = 0U; i < contexts_.size(); ++i) {
            contexts_[i].guard =
                std::make_unique<boost::asio::executor_work_guard<
                    boost::asio::io_context::executor_type>>(
                    boost::asio::make_work_guard(contexts_[i].io_context));
        }
    }

    void run() {
        for (auto i = 0U; i < contexts_.size(); ++i) {
            contexts_[i].thread =
                std::thread([i, this] { contexts_[i].io_context.run(); });
        }
        for (auto i = 0U; i < contexts_.size(); ++i) {
            contexts_[i].thread.join();
        }
    }

    void stop() {
        for (auto i = 0U; i < contexts_.size(); ++i) {
            contexts_[i].io_context.stop();
        }
    }

    boost::asio::io_context& io_context() {
        if (next_context_ == contexts_.size()) {
            next_context_ = 0U;
        }
        return contexts_[next_context_++].io_context;
    }

private:
    struct context {
        boost::asio::io_context io_context;
        std::unique_ptr<boost::asio::executor_work_guard<
            boost::asio::io_context::executor_type>>
            guard;
        std::thread thread;
    };
    std::vector<context> contexts_;
    size_t next_context_{};
};

}  // namespace detail
}  // namespace rpc
