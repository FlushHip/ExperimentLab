#include <iostream>

#include "first/lib.h"
#include "second/lib.h"
#include "third/lib.h"

namespace lib_static {
namespace main {

void print() {
    std::cout << __FUNCTION__ << std::endl;
    std::cout << "\t" << &a::global_var() << std::endl;
    std::cout << "\t" << &a::static_var() << std::endl;
}

}  // namespace main
}  // namespace lib_static

int main(int argc, char** argv) {
    lib_static::main::print();
    lib_static::b::print();
    lib_static::c::print();

    return 0;
}
