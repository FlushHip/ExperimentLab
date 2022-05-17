#include <iostream>

#include "min.hpp"

struct X1 {};
bool operator< (const X1 &, const X1 &) { return true; };

struct X2 {};
bool operator< (X2, X2) { return true; };

struct X3 {};

struct X4 {
    bool operator< (const X4 &) const { return true; }
};

struct BoolConvertible {
    operator bool() const { return true; }
};
struct X5{};
auto operator< (const X5 &, const X5 &) { return BoolConvertible{}; };


struct NoBoolConvertible {
    operator bool() const { return true; }
};
struct X6{};
auto operator< (const X6 &, const X6 &) { return NoBoolConvertible{}; };

struct BoolLike {
    explicit operator bool() const { return true; }
};
struct X7{};
auto operator< (const X7 &, const X7 &) { return BoolLike{}; };

int main(int argc, char* argv[]) {
    min_1::min(X1{}, X1{});
    min_1::min(X2{}, X2{});
    //min_1::min(X3{}, X3{});
    min_1::min(X4{}, X4{});
    min_1::min(X5{}, X5{});
    min_1::min(X6{}, X6{});
    //min_1::min(X7{}, X7{});

    min_2::min(X1{}, X1{});
    min_2::min(X2{}, X2{});
    //min_2::min(X3{}, X3{});
    min_2::min(X4{}, X4{});
    min_2::min(X5{}, X5{});
    min_2::min(X6{}, X6{});
    min_2::min(X7{}, X7{});
    return 0;
}
