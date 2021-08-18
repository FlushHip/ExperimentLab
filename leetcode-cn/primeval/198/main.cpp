#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::vector<int> A{ 1, 2, 3, 1 };
    std::vector<int> B{ 2, 7, 9, 3, 1 };
    std::cout << sol.rob(A) << std::endl;
    std::cout << sol.rob(B) << std::endl;
    return 0;
}
