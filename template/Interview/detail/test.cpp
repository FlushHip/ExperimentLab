#include <iostream>

#include <dbg-macro/dbg.h>
#include <nlohmann/json.hpp>

namespace hestina {

struct any {
    template <typename T>
    operator T();
};

template <typename T, typename... Args>
consteval auto member_count() {
    if constexpr (!requires { T{{Args{}}..., {any{}}}; }) {
        return sizeof...(Args);
    } else {
        return member_count<T, Args..., any>();
    }
}

template <typename... Args>
std::string visitor(Args&&... args) {
    std::ostringstream os;
    // (os << ... << args);
    (..., (os << args << ", "));
    return os.str();
}

template <typename T>
constexpr decltype(auto) visit_members(T&& object) {
    constexpr auto cnt = member_count<T>();
    if constexpr (cnt == 0) {
        return visitor();
    }
    if constexpr (cnt == 1) {
        auto&& [a1] = object;
        return visitor(a1);
    }
    if constexpr (cnt == 2) {
        auto&& [a1, a2] = object;
        return visitor(a1, a2);
    }
}

template <typename T, std::enable_if_t<std::is_aggregate_v<T>, void>* = 0>
std::ostream& operator<<(std::ostream& os, const T& object) {
    return os << visit_members(object);
}

};  // namespace hestina

struct context_t {
    std::string name;
    int age;
    // NLOHMANN_DEFINE_TYPE_INTRUSIVE(context_t, name, age);
};

int main() {
    // dbg(nlohmann::json(context_t{"flushhip", 27}).dump());
    // dbg(hestina::visit_members(context_t{"flushhip", 27}));
    dbg((context_t{"flushhip", 27}));
    return 0;
}
