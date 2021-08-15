#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::vector<int> A{ 3, 0 , 1 };
    std::vector<int> B{ 9, 6, 4, 2, 3, 5, 7, 0, 1 };

    std::cout << sol.missingNumber(A) << std::endl;
    std::cout << sol.missingNumber(B) << std::endl;
    return 0;
}
