#define DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <hestina/log/logger.h>

struct dummy_t {
    dummy_t() {
        hestina::logger::instance().init(hestina::logger::level_t::finer);
    }
} dummy;
