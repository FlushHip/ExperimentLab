#pragma once

#include <type_traits>

template<typename T1, typename T2>
struct HasLess {
private:
    template<typename U1, typename U2>
    static auto check(int) -> decltype(std::declval<U1>() < std::declval<U2>(), std::true_type());

    template<typename U1, typename U2>
    static auto check(...) -> std::false_type;
public:
    static constexpr bool value = decltype(check<T1, T2>(0))::value;
};

template<typename T1, typename T2>
constexpr auto HasLess_v = HasLess<T1, T2>::value;

template<typename T1, typename T2, bool HasLess>
struct LessResultImpl {};

template<typename T1, typename T2>
struct LessResultImpl<T1, T2, true> {
    using type = decltype(std::declval<T1>() < std::declval<T2>());
};

template<typename T1, typename T2>
struct LessResult : public LessResultImpl<T1, T2, HasLess_v<T1, T2>> {};

template<typename T1, typename T2>
using LessResult_t = typename LessResult<T1, T2>::type;

template<typename T>
struct IsContextualBool {
private:
    template<typename U>
    static auto check(int) -> decltype((std::declval<U>() ? 0 : 1), std::true_type());

    template<typename U>
    static auto check(...) -> std::false_type;
public:
    static constexpr bool value = decltype(check<T>(0))::value;
};

template<typename T>
constexpr auto IsContextualBool_v = IsContextualBool<T>::value;

namespace min_1 {
/*
template<typename T
    , std::enable_if_t<std::is_convertible_v<LessResult<const T &, const T &>, bool>> * = 0>
const T & min(const T & a, const T & b) {
    return a < b ? a : b;
}
*/
template<typename T>
std::enable_if_t<std::is_convertible_v<LessResult_t<const T &, const T &>, bool>, const T &>
    min(const T & a, const T & b) {
    return a < b ? a : b;
}
}

namespace min_2 {
template<typename T
    //, std::enable_if_t<IsContextualBool_v<LessResult_t<const T &, const T &>>> * = 0>
    , typename = std::enable_if_t<IsContextualBool_v<LessResult_t<const T &, const T &>>>>
const T & min(const T & a, const T & b) {
    return a < b ? a : b;
}
}
