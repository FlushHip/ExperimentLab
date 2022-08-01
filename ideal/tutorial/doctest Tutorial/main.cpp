#include <doctest/doctest.h>

int fact(int n) {
    return n ? n * fact(n - 1) : 1;
}

TEST_CASE("fact") {
    // CHECK(fact(0) == 0);
    CHECK(fact(1) == 1);
    CHECK(fact(3) == 6);

    SUBCASE("nice") {
        CHECK(fact(1 * 3) == fact(3 * 1));
        SUBCASE("too") {
            CHECK(true);
        }
    }
    SUBCASE("nice2") {
        CHECK_EQ(fact(1 * 3), fact(3 * 1));
    }
}

TEST_CASE("vectors can be sized and resized") {
    std::vector<int> v(5);

    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 5);

    SUBCASE("adding to the vector increases it's size") {
        v.push_back(1);

        CHECK(v.size() == 6);
        CHECK(v.capacity() >= 6);
    }
    SUBCASE("reserving increases just the capacity") {
        v.reserve(6);

        CHECK(v.size() == 5);
        CHECK(v.capacity() >= 6);
    }
}
