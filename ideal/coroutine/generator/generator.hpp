
#pragma once

#include <coroutine>
#include <exception>
#include <type_traits>
#include <utility>

namespace cpp_co {

template <typename T = int>
struct generator {
    generator(const generator&) = delete;
    generator& operator=(const generator&) = delete;

    struct promise_type;
    generator(std::coroutine_handle<promise_type> handle) : handle(handle) {}
    generator(generator&& other) noexcept
        : handle(std::exchange(other.handle, {})) {}
    ~generator() {
        if (handle) {
            handle.destroy();
        }
    }

    struct promise_type {
        std::suspend_always initial_suspend() { return {}; }

        std::suspend_always final_suspend() noexcept { return {}; }

        void unhandled_exception() { exp = std::current_exception(); }

        generator get_return_object() {
            return {std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        // std::suspend_always await_transform(int value) {
        std::suspend_always yield_value(T value) {
            this->value = value;
            is_ready = true;
            return {};
        }

        void return_void() {}

        T value{};
        bool is_ready{false};
        std::exception_ptr exp{nullptr};
    };

    class exhausted_exception : std::exception {};

    [[nodiscard]] bool has_next() const {
        if (handle.done()) {
            return false;
        }
        if (!handle.promise().is_ready) {
            handle.resume();
        }
        return !handle.done();
    }

    [[nodiscard]] T next() const {
        if (has_next()) {
            handle.promise().is_ready = false;
            return handle.promise().value;
        }
        throw exhausted_exception{};
    }

    template <typename F>
    generator<std::invoke_result_t<F, T>> map(F&& f) {
        while (has_next()) {
            // co_yield std::forward<F>(f)(next());
            co_yield std::invoke(std::forward<F>(f), next());
        }
    }

    template <typename F>
    std::invoke_result_t<F, T> fmap(F&& f) {
        while (has_next()) {
            generator<T> gen = std::forward<F>(f)(next());
            while (gen.has_next()) {
                co_yield gen.next();
            }
        }
    }

    template <typename F>
    void for_each(F&& f) {
        while (has_next()) {
            std::forward<F>(f)(next());
        }
    }

    template <typename F, typename R>
    R fold(F&& f, R&& init) {
        R result = std::forward<R>(init);
        while (has_next()) {
            result = std::invoke(std::forward<F>(f), result, next());
        }
        return result;
    }

    T sum() {
        T result{0};
        while (has_next()) {
            result += next();
        }
        return result;
    }

    template <typename F>
    generator<T> filter(F&& f) {
        while (has_next()) {
            auto value = next();
            if (std::invoke(std::forward<F>(f), value)) {
                co_yield value;
            }
        }
    }

    generator<T> take(int n) {
        for (int i = 0; i < n && has_next(); ++i) {
            co_yield next();
        }
    }

    template <typename... Args>
    static generator<T> from(Args&&... args) {
        (co_yield std::forward<Args>(args), ...);
    }

    static generator<T> range(int begin, int end) {
        for (int i = begin; i < end; ++i) {
            co_yield i;
        }
    }

    std::coroutine_handle<promise_type> handle;
};

}  // namespace cpp_co
