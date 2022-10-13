#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::vector<int>> v{
        { 1, 0, 5 },
        { 0, 3, 0 },
        { 0, 2, 0 },
        { 0 },
        { 1, 1 },
        { 0, 0, 10, 0, 0, 0, 10, 0, 0, 0 },
        { 9, 1, 8, 8, 9 },
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->findMinMoves(v[L]);

        std::cout << ans
            << std::endl << std::endl;
    }

    return 0;
}
