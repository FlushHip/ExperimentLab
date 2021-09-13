#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 3;

    auto sol = std::make_unique<Solution>();

    std::vector<std::vector<int>> points[EN]{
        { { 0, 0 }, { 1, 0 }, { 2, 0 } },
        { { 1, 1 }, { 2, 2 }, { 3, 3 } },
        { { 1, 1 } },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->numberOfBoomerangs(points[L]);

        std::cout << ans
            << std::endl << std::endl;
    }

    return 0;
}
