#include <functional>
#include <iostream>
#include <string>

#include <doctest/doctest.h>

#include "result.hpp"

TEST_CASE("test") {
    cpp_co::result<int>{};
    cpp_co::result<int>{5};
}
