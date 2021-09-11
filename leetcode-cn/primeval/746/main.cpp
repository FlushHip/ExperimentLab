#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 2;

    auto sol = std::make_unique<Solution>();

    std::vector<int> cost[EN]{
        { 10, 15, 20 },
        { 1, 100, 1, 1, 1, 100, 1, 1, 100, 1 },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->minCostClimbingStairs(cost[L]);

        std::cout
            << std::endl << std::endl;
    }

    return 0;
}
