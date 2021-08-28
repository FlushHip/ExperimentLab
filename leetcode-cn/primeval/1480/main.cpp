#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::vector<int> A{ 1, 2, 3, 4 };
    std::vector<int> B{ 1, 1, 1, 1, 1 };
    std::vector<int> C{ 3, 1, 2, 10, 1 };

    std::cout << sol.runningSum(A) << std::endl;
    std::cout << sol.runningSum(B) << std::endl;
    std::cout << sol.runningSum(C) << std::endl;

    return 0;
}
