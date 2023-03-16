#pragma once

#include <functional>
#include <memory>
#include <tuple>
#include <type_traits>
#include <unordered_map>

#include "logger.hpp"

namespace rpc {
namespace detail {

namespace traits {}

class connection;

class router {
public:
    template <typename F>
    void rigister(const std::string& method, F f) {
        invokers_[method] = [f = std::move(f)](std::weak_ptr<connection> conn,
                                std::string_view buffer, std::string& result) {
            apply(std::move(f), conn, buffer, result);
        };
    }

    // tmp
    void route(const std::string& method) {
        auto it = invokers_.find(method);
        if (it != invokers_.end()) {
            std::string result;
            it->second(std::weak_ptr<rpc::detail::connection>{}, {}, result);
            LOG_INFO << result;
        }
    }

private:
    template <typename F>
    // struct apply_ctx {
    static void apply(F&& f,
        std::weak_ptr<connection> conn,
        std::string_view buffer,
        std::string& result) {
        auto tpl = std::make_tuple<int, std::string, float>(1, "nice", 0.5);

        call(std::forward<F>(f), conn, std::move(tpl), result);
    }
    //};

    template <typename F, typename... Args>
    static std::enable_if_t<std::is_void_v<
        std::invoke_result_t<F, std::weak_ptr<connection>, Args...>>>
    call(F&& f,
        std::weak_ptr<connection> conn,
        std::tuple<Args...>&& tpl,
        std::string& result) {
        auto fun = [&f, conn](auto&&... args) {
            f(conn, std::forward<decltype(args)>(args)...);
        };
        std::apply(std::move(fun), std::move(tpl));
        result = "ok";
    }

    template <typename F, typename... Args>
    // static std::enable_if_t<!std::is_void_v<
    // std::invoke_result_t<F, std::weak_ptr<connection>, Args...>>>
    static typename std::enable_if<!std::is_void<typename std::result_of<
        F(std::weak_ptr<connection>, Args...)>::type>::value>::type
    call(F&& f,
        std::weak_ptr<connection> conn,
        std::tuple<Args...>&& tpl,
        std::string& result) {
        auto fun = [&f, conn](auto&&... args) {
            return f(conn, std::forward<decltype(args)>(args)...);
        };
        auto res = std::apply(std::move(fun), std::move(tpl));
        result = "ok";
        // TODO(flushhip): serialize res
    }

private:
    using internal_handler = std::function<
        void(std::weak_ptr<connection>, std::string_view, std::string&)>;
    std::unordered_map<std::string, internal_handler> invokers_;
};

}  // namespace detail
}  // namespace rpc
