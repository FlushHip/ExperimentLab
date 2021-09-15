#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 3;

    auto sol = std::make_unique<Solution>();

    std::vector<int> nums[EN]{
        { 1, 2, 3, 1 },
        { 1, 2, 1, 3, 5, 6, 4 },
        { 1 },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->findPeakElement(nums[L]);

        std::cout << ans
            << std::endl << std::endl;
    }

    return 0;
}
