#include "lib.h"

#include <iostream>

namespace lib_static {
namespace a {

int global_i = 0;
int& static_var() {
    static int i = 0;
    return i;
}

int& global_var() {
    return global_i;
}

void print() {
    std::cout << &global_i << std::endl;
    std::cout << &static_var() << std::endl;
}

}  // namespace a
}  // namespace lib_static
