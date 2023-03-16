#include <functional>
#include <iostream>
#include <string>

#include <doctest/doctest.h>

#include "generator.hpp"

cpp_co::generator<int> sequence() {
    for (int i = 0; i < 5; ++i) {
        // co_await i;
        co_yield i;  //  == co_await promise.yield_value(i)
    }
}

cpp_co::generator<int> fib() {
    int a = 1;
    int b = 1;
    co_yield a;
    co_yield b;
    for (int i = 2; i < 50; ++i) {
        b = a + b;
        co_yield b;
        a = b - a;
    }
}

TEST_CASE("sample use") {
    auto gen_a = sequence();
    for (int i = 0; i < 10 && gen_a.has_next(); ++i) {
        std::cout << gen_a.next() << std::endl;
    }
    auto gen_b = fib();
    for (int i = 0; i < 20 && gen_b.has_next(); ++i) {
        std::cout << gen_b.next() << std::endl;
    }
}

TEST_CASE("map") {
    cpp_co::generator<int>::range(0, 10).for_each(
        [](auto value) { std::cout << value; });
    std::cout << "\n";

    cpp_co::generator<int>::range(0, 5)
        .map([](int value) { return std::to_string(value * 2); })
        .for_each([](const std::string& value) { std::cout << value; });
    std::cout << "\n";
}

TEST_CASE("fmap") {
    cpp_co::generator<int>::from(1, 2, 3, 4)
        .fmap([](const auto& value) -> cpp_co::generator<int> {
            for (int i = 0; i < value; ++i) {
                co_yield i;
            }
        })
        .for_each([f = true](const auto& value) mutable {
            if (f) {
                f = false;
                std::cout << "*";
            } else if (value == 0) {
                std::cout << std::endl;
                std::cout << "*";
            } else {
                std::cout << " *";
            }
        });
}

TEST_CASE("sum") {
    CHECK(cpp_co::generator<>::range(1, 11).sum() == 55);
}

TEST_CASE("fold") {
    CHECK(cpp_co::generator<>::range(1, 4).fold(std::multiplies<>{}, 1) == 6);
}

TEST_CASE("generator chain of the use of lambda") {
    cpp_co::generator<>::range(1, 11)
        .filter([](auto i) {
            std::cout << "filter : " << i << std::endl;
            return i % 2 == 0;
        })
        .map([](auto i) {
            std::cout << "map : " << i << std::endl;
            return i * 3;
        })
        .fmap([](auto value) -> cpp_co::generator<> {
            std::cout << "fmap : " << value << std::endl;
            for (int i = 1; i <= value; ++i) {
                co_yield i;
            }
        })
        .take(20)
        .for_each([](auto i) { std::cout << "for_each : " << i << std::endl; });
}
