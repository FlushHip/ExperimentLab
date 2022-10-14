#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::tuple<int, int, int>> v{
        { 1, 1, 7 },
        { 2, 2, 1 },
        { 7, 1, 0 },
        { 1, 1, 1 },
        { 3, 3, 3 },
        { 0, 0, 0 },
        { 0, 0, 1 },
        { 0, 0, 2 },
        { 0, 0, 3 },
        { 2, 0, 2 },
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->longestDiverseString(
            std::get<0>(v[L]), std::get<1>(v[L]), std::get<2>(v[L]));

        std::cout << ans
            << std::endl << std::endl;
    }

    return 0;
}
