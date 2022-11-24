#include <iostream>

#include "log/logger.h"

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::trace);

    return 0;
}
