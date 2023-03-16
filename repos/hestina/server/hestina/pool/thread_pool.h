#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace hestina {

class thread_pool {
public:
    thread_pool(std::size_t nums = std::thread::hardware_concurrency()) {
        for (std::size_t i = 0; i < nums; ++i) {
            threads_.emplace_back([this] { run(); });
        }
    }

    ~thread_pool() {
        is_running_ = false;
        tasks_convar_.notify_all();
        for (std::size_t i = 0; i < threads_.size(); ++i) {
            if (threads_[i].joinable()) {
                threads_[i].join();
            }
        }
    }

    template <class F, class... Args>
    auto commit(F&& f, Args&&... args) {
        using return_type = std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        auto ret = task->get_future();
        {
            std::lock_guard<std::mutex> lock(tasks_mutex_);
            tasks_.emplace([task] { (*task)(); });
        }

        tasks_convar_.notify_one();
        return ret;
    }

private:
    using task_type = std::function<void()>;

    void run() {
        while (true) {
            task_type task;
            {
                std::unique_lock<std::mutex> lock(tasks_mutex_);
                tasks_convar_.wait(
                    lock, [this] { return !is_running_ || !tasks_.empty(); });
                if (!is_running_ && tasks_.empty()) {
                    return;
                }
                if (!tasks_.empty()) {
                    task = std::move(tasks_.front());
                    tasks_.pop();
                }
            }
            task();
        }
    }

    std::atomic_bool is_running_{true};

    std::vector<std::thread> threads_;

    std::mutex tasks_mutex_;
    std::condition_variable tasks_convar_;
    std::queue<task_type> tasks_;
};

class work_thread : public thread_pool {
public:
    work_thread() : thread_pool(1) {}
};

}  // namespace hestina
