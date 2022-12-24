#include <hestina/log/logger.h>

struct dummy_t {
    dummy_t() {
        hestina::logger::instance().init(hestina::logger::level_t::finer);
    }
} dummy;
