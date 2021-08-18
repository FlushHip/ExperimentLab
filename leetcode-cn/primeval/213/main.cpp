#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::vector<int> A{ 2, 3, 2 };
    std::vector<int> B{ 1, 2, 3, 1 };
    std::vector<int> C{ 0 };
    std::vector<int> D{ 1 };
    std::cout << sol.rob(A) << std::endl;
    std::cout << sol.rob(B) << std::endl;
    std::cout << sol.rob(C) << std::endl;
    std::cout << sol.rob(D) << std::endl;
    return 0;
}
