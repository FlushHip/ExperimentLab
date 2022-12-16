#include "log/logger.h"

#include <doctest/doctest.h>

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::finer, true);

    doctest::Context context(argc, argv);
    int ret = context.run();
    return ret;
}
