#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::pair<int, std::vector<std::vector<int>>>> v{
        { 5, {
            { 1, 4, 7, 11, 15 },
            { 2, 5, 8, 12, 19 },
            { 3, 6, 9, 16, 22 },
            { 10, 13, 14, 17, 24 },
            { 18, 21, 23, 26, 30 },
        } },
        { 20, {
            { 1, 4, 7, 11, 15 },
            { 2, 5, 8, 12, 19 },
            { 3, 6, 9, 16, 22 },
            { 10, 13, 14, 17, 24 },
            { 18, 21, 23, 26, 30 },
        } },
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->searchMatrix(v[L].second, v[L].first);

        std::cout << std::boolalpha << ans
            << std::endl << std::endl;
    }

    return 0;
}
