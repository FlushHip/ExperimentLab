#include <iostream>
#include <iomanip>

#include "aop.hpp"

#define AOP_TEST(INDEX)\
struct aop_test_##INDEX {\
    void aop_before(int a, int b) {\
        std::cout << INDEX << " aop_before: " << a << ", " << b << std::endl;\
    }\
    void aop_after(int a, int b) {\
        std::cout << INDEX << " aop_after: " << a << ", " << b << std::endl;\
    }\
};

AOP_TEST(1)
AOP_TEST(2)
AOP_TEST(3)
AOP_TEST(4)
AOP_TEST(5)

struct aop_test_no {
    void aop_before(int a, int b) {}
};

int main(int argc, char* argv[]) {
    invoke<aop_test_1, aop_test_2, aop_test_3, aop_test_4, aop_test_no, aop_test_5>(
        [](int a, int b) {
        std::cout << "lambda: " << a << ", " << b << std::endl;
    }, 1, 2);
}
