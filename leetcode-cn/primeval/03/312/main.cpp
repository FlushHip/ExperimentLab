#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 2;

    auto sol = std::make_unique<Solution>();

    std::vector<int> nums[EN]{
        { 3, 1, 5, 8 },
        { 1, 5 },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        int ans = sol->maxCoins(nums[L]);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
