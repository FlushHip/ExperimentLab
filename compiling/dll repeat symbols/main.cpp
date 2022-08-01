#include <iostream>

#include "first/lib.h"
#ifdef CASE_1
#  include "second/lib.h"
#elif defined(CASE_2)
#  include "third/lib.h"
#endif

int main(int argc, char** argv) {
#ifdef CASE_1
    std::cout << "--------------------------------" << std::endl;
    lib_a();
    std::cout << "--------------------------------" << std::endl;
    lib_b();
    std::cout << "--------------------------------" << std::endl;
    lib_func();
    std::cout << "--------------------------------" << std::endl;
#elif defined(CASE_2)
    std::cout << "--------------------------------" << std::endl;
    lib_a();
    std::cout << "--------------------------------" << std::endl;
    lib_c();
    std::cout << "--------------------------------" << std::endl;
    lib_func();
    std::cout << "--------------------------------" << std::endl;
#endif
    return 0;
}
