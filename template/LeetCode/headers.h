#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <charconv>
#include <complex>
#include <cstring>
#include <functional>
#include <limits>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <regex>
#include <span>
#include <tuple>
#include <type_traits>
#include <utility>

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>

#include "prettyprint.hpp"

using namespace std;
using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;
using namespace std::literals::chrono_literals;
using namespace std::literals::complex_literals;

template <class T = int>
using VList = std::vector<T>;

template <class... Args>
using VTList = std::vector<std::tuple<Args...>>;

namespace aux {
// f signture can't have & or &&, if have, please use macro `UNPACK_*`
template <class F, class T0, class T1>
constexpr decltype(auto) call(F&& f, T0& ptr, T1&& t) {
    return std::invoke(std::forward<F>(f), ptr.get(), std::forward<T1>(t));
}

template <class F, class T0, class... TN>
constexpr decltype(auto) call(F&& f, T0& ptr, std::tuple<TN...>& arg) {
    return std::apply(std::forward<F>(f),
        std::tuple_cat(std::forward_as_tuple(ptr.get()), arg));
}

}  // namespace aux

template <class T, std::size_t N>
std::ostream& operator<<(std::ostream& os, std::span<T, N>&& view) {
    os << "[";
    for (auto i = 0U; i < view.size(); ++i) {
        os << (i == 0U ? "" : ", ") << view[i];
    }
    os << "]";
    return os;
}

#define UNPACK_2(vp) std::get<0>(vp), std::get<1>(vp)
#define UNPACK_3(vp) UNPACK_2(vp), std::get<2>(vp)
#define UNPACK_4(vp) UNPACK_3(vp), std::get<3>(vp)
#define UNPACK_5(vp) UNPACK_4(vp), std::get<4>(vp)
#define UNPACK_6(vp) UNPACK_5(vp), std::get<5>(vp)
#define UNPACK_7(vp) UNPACK_6(vp), std::get<6>(vp)
