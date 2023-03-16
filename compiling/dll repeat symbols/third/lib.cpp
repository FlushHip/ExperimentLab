#include "lib.h"

#include <iostream>

namespace {
void func() {
    std::cout << "local third" << std::endl;
}
}  // namespace

void lib_c() {
    std::cout << "start third" << std::endl;
    lib_func();
    func();
}

void lib_func() {
    std::cout << "export third" << std::endl;
}
