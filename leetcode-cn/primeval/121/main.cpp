#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::vector<int> A{ 7, 1, 5, 3, 6, 4 };
    std::vector<int> B{ 7, 6, 4, 3, 1 };
    std::vector<int> C{ 7 };

    std::cout << sol.maxProfit(A) << std::endl;
    std::cout << sol.maxProfit(B) << std::endl;
    std::cout << sol.maxProfit(C) << std::endl;

    return 0;
}
