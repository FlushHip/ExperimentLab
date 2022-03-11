#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::pair<std::vector<int>, int>> v{
        { { 1, 2, 0, 0 }, 34 },
        { { 2, 7, 4 }, 181},
        { { 2, 1, 5 }, 806},
        { { 1, 1, 1, 1 }, 9999 },
        { { 1 }, 99999 },
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :" << std::endl;

        std::cout << "\t\x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto ans = sol->addToArrayForm(v[L].first, v[L].second);

        std::cout << "\t\x1b[31mans -> \x1b[0m" << ans
            << std::endl << std::endl;
    }

    return 0;
}
