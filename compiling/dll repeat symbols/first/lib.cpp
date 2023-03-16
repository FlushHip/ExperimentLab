#include "lib.h"

#include <iostream>

namespace {
void func() {
    std::cout << "local first" << std::endl;
}
}  // namespace

void lib_a() {
    std::cout << "start first" << std::endl;
    lib_func();
    func();
}

void lib_func() {
    std::cout << "export first" << std::endl;
}
