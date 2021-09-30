#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::pair<std::vector<int>, std::vector<int>>> v{
        { { 0, 0, 2, 2 }, { 1, 1, 3, 3 } },
        { { 0, 0, 1, 1 }, { 1, 0, 2, 1 } },
        { { 0, 0, 1, 1 }, { 2, 2, 3, 3 } },
        { { 7, 8, 13, 15 }, { 10, 8, 12, 20 } },
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->isRectangleOverlap(v[L].first, v[L].second);

        std::cout << std::boolalpha << ans
            << std::endl << std::endl;
    }

    return 0;
}
