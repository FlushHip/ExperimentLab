#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::vector<int> A{ 1, 2, 3, 0, 2 };
    std::vector<int> B{ 2, 1 };
    std::vector<int> C{ 2, 1, 4 };

    std::cout << sol.maxProfit(A) << std::endl;
    std::cout << sol.maxProfit(B) << std::endl;
    std::cout << sol.maxProfit(C) << std::endl;
    return 0;
}
