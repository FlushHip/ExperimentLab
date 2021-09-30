#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::vector<int>> v{
        { -3, 0, 3, 4, 0, -1, 9, 2 },
        { -2, -2, 2, 2, -2, -2, 2, 2 },
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->computeArea(v[L][0], v[L][1], v[L][2], v[L][3]
            , v[L][4], v[L][5], v[L][6], v[L][7]);

        std::cout << ans
            << std::endl << std::endl;
    }

    return 0;
}
