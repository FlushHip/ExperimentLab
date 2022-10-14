#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    std::vector<int> A{ 1, 4, 2, 5, 3 };
    std::vector<int> B{ 1, 2 };
    std::vector<int> C{ 10, 11, 12 };
    std::vector<int> D{ 1 };

    std::cout << sol->sumOddLengthSubarrays(A) << std::endl;
    std::cout << sol->sumOddLengthSubarrays(B) << std::endl;
    std::cout << sol->sumOddLengthSubarrays(C) << std::endl;
    std::cout << sol->sumOddLengthSubarrays(D) << std::endl;

    return 0;
}
