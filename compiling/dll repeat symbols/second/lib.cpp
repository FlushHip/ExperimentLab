#include "lib.h"

#include <iostream>

namespace {
void func() {
    std::cout << "local second" << std::endl;
}
}  // namespace

void lib_b() {
    std::cout << "start second" << std::endl;
    lib_func();
    func();
}

void lib_func() {
    std::cout << "export second" << std::endl;
}
