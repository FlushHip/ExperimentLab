#include "lib.h"

#include <iostream>

#include "../first/lib.h"

namespace lib_static {
namespace c {

void print() {
    std::cout << __FUNCTION__ << std::endl;
    std::cout << "\t" << &a::global_var() << std::endl;
    std::cout << "\t" << &a::static_var() << std::endl;
}

}  // namespace c
}  // namespace lib_static
