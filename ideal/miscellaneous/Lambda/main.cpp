#include <iostream>
#include <memory>
#include <vector>
#include <functional>

void f() {
    static int cnt = 0;
    auto lambdaA = [] () {
        std::cout << __LINE__ << " : " << cnt << std::endl;
    };
    auto lambdaB = [=] () {
        std::cout << __LINE__ << " : " << cnt << std::endl;
    };
    auto lambdaC = [&] () {
        std::cout << __LINE__ << " : " << cnt << std::endl;
    };
    auto lambdaD = [cnt = cnt] () {
        std::cout << __LINE__ << " : " << cnt << std::endl;
    };

    std::vector<std::function<void(void)>> funs {
        lambdaA,
        lambdaB,
        lambdaC,
        lambdaD,
    };

    for (const auto & fun : funs) {
        fun();
    }

    ++cnt;
}

int main(int argc, char **argv)
{
    for (int i = 0; i < 3; ++i) {
        std::cout << "index " << i + 1 << std::endl;
        f();
        std::cout << std::endl;
    }
    return 0;
}
