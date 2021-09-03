#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 5;

    auto sol = std::make_unique<Solution>();

    std::vector<int> height[EN]{
        { 1, 8, 6, 2, 5, 4, 8, 3, 7 },
        { 1, 1 },
        { 4, 3, 2, 1, 4 },
        { 1, 2, 1 },
        { 2, 1},
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        int ans = sol->maxArea(height[L]);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
