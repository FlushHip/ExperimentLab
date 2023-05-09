#pragma once

#include <coroutine>
#include <exception>
#include <optional>

#include "result.hpp"

namespace cpp_co {

template <typename T>
struct task {
    struct task_promise;
    using promise_type = task_promise;

    struct task_promise {
        std::suspend_always initial_suspend() { return {}; }

        std::suspend_always final_suspend() { return {}; }

        task<T> get_return_object() {
            return task{
                std::coroutine_handle<task_promise>::from_promise(*this)};
        }

        void return_value(T value) { res = result<T>{std::move(value)}; }

        void unhandled_exception() {
            res = result<T>{std::current_exception()};
        }

        std::optional<result<T>> res{};
    };
};

}  // namespace cpp_co
