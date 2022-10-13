#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::pair<std::vector<int>, std::vector<int>>> v{
        {
            { -1, 0, 0, 2 },
            { 1, 2, 3, 4 },
        },
        {
            { -1, 0, 1, 0, 3, 3 },
            { 5, 4, 6, 2, 1, 3 },
        },
        {
            { -1, 2, 3, 0, 2, 4, 1 },
            { 2, 3, 4, 5, 6, 7, 8 },
        },
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :" << std::endl;

        std::cout << "\t\x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto ans = sol->smallestMissingValueSubtree(v[L].first, v[L].second);

        std::cout << "\t\x1b[31mans -> \x1b[0m" << ans
            << std::endl << std::endl;
    }

    return 0;
}
