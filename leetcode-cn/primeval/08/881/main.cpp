#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::vector<int> A{ 1, 2 };
    std::vector<int> B{ 3, 2, 2, 1 };
    std::vector<int> C{ 3, 5, 3, 4 };
    std::vector<int> D{ 1 };

    std::cout << sol.numRescueBoats(A, 3) << std::endl;
    std::cout << sol.numRescueBoats(B, 3) << std::endl;
    std::cout << sol.numRescueBoats(C, 5) << std::endl;
    std::cout << sol.numRescueBoats(D, 1) << std::endl;

    return 0;
}
