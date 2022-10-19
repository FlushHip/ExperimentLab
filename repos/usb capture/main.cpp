#include "app.h"

#include "logger.hpp"

int main(int argc, char** argv) {
    hestina::detail::logger::init();

    return hestina::app::get().run(argc, argv);
}
