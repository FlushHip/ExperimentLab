#include <doctest/doctest.h>

#include <hestina/util/funs.h>

TEST_CASE("util funs") {
    uint64_t value = 15634684651653165;
    CHECK(hestina::util::ntoh64(hestina::util::hton64(value)) == value);
}
