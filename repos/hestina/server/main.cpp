#include <iostream>

#include "log/logger.h"
#include "pool/thread_pool.h"

int main(int argc, char* argv[]) {
    hestina::logger::instance().init(hestina::logger::trace);

    return 0;
}
