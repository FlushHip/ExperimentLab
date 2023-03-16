#pragma once

#include <type_traits>

template<typename... Types>
struct MatchOverloads;

template<>
struct MatchOverloads<> {
    static void match(...);
};

template<typename T, typename... Types>
struct MatchOverloads<T, Types...> : public MatchOverloads<Types...> {
    static T match(T);
    using MatchOverloads<Types...>::match;
};

template<typename T, typename... Types>
struct BestMatchInSet {
    using type = decltype(MatchOverloads<Types...>::match(std::declval<T>()));
};

template<typename T, typename... Types>
using BestMatchInSet_t = typename BestMatchInSet<T, Types...>::type;
