#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    std::vector<std::vector<int>> A {
        { 2, 1, 1 },
        { 2, 3, 1 },
        { 3, 4, 1 },
    };
    std::vector<std::vector<int>> B {
        { 1, 2, 1 },
    };

    std::cout << sol->networkDelayTime(A, 4, 2) << std::endl;
    std::cout << sol->networkDelayTime(B, 2, 1) << std::endl;
    std::cout << sol->networkDelayTime(B, 2, 2) << std::endl;

    return 0;
}
