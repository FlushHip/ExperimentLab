#pragma once

#include <exception>
#include <variant>

namespace cpp_co {

template <typename T>
struct result {
    result() = default;
    result(T&& t) : value(t) {}
    result(std::exception_ptr&& e) : value(e) {}

    T get() const {
        if (std::get<std::exception_ptr>(value)) {
            std::rethrow_exception(value);
        }
        return value;
    }

    std::variant<std::monostate, T, std::exception_ptr> value;
};

}  // namespace cpp_co
