#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::pair<std::string, std::vector<std::vector<int>>>> v{
        { "**|**|***|", {
            { 2, 5 },
            { 5, 9 },
        } },
        { "***|**|*****|**||**|*", {
            { 1, 17 },
            { 4, 5 },
            { 14, 17 },
            { 5, 11 },
            { 15, 16 },
        } },
        { "*", {
            { 0, 0 },
        } },
        { "|", {
            { 0, 0 },
        } },
        { "|*|", {
            { 0, 0 },
            { 1, 1 },
            { 2, 2 },
            { 0, 1 },
            { 0, 2 },
            { 1, 2 },
        } },
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :" << std::endl;

        std::cout << "\t\x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto ans = sol->platesBetweenCandles(v[L].first, v[L].second);

        std::cout << "\t\x1b[31mans -> \x1b[0m" << ans
            << std::endl << std::endl;
    }

    return 0;
}
