#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

#include <algorithm>
#include <bitset>
#include <charconv>
#include <complex>
#include <cstring>
#include <functional>
#include <limits>
#include <memory>
#include <numeric>
#include <random>
#include <regex>
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
template <class F, class T0, class T1>
constexpr decltype(auto) call(F&& f, T0& ptr, T1&& t) {
    return std::invoke(std::forward<F>(f), ptr.get(), std::forward<T1>(t));
}

template <class F, class T0, class... TN>
constexpr decltype(auto) call(F&& f, T0& ptr, std::tuple<TN...>& arg) {
    return std::apply(std::forward<F>(f),
        std::tuple_cat(std::forward_as_tuple(ptr.get()), std::move(arg)));
}

}  // namespace aux
