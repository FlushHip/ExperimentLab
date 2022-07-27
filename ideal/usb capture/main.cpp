#include "app.h"

#include "logger.hpp"

int main(int argc, char** argv) {
    hestina::detail::logger::init();
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    return hestina::app::get().run(argc, argv);
}
