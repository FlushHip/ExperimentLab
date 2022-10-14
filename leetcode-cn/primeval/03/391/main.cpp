#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::vector<std::vector<int>>> v{
        {
            { 1, 1, 3, 3 },
            { 3, 1, 4, 2 },
            { 3, 2, 4, 4 },
            { 1, 3, 2, 4 },
            { 2, 3, 3, 4 },
        },
        {
            { 1, 1, 2, 3 },
            { 1, 3, 2, 4 },
            { 3, 1, 4, 2 },
            { 3, 2, 4, 4 },
        },
        {
            { 1, 1, 3, 3 },
            { 3, 1, 4, 2 },
            { 1, 3, 2, 4 },
            { 2, 2, 4, 4 },
        },
        {
            { 0, 0, 1, 1 },
            { 0, 1, 3, 2 },
            { 1, 0, 2, 2 },
        }
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :" << std::endl;

        std::cout << "\t\x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto ans = sol->isRectangleCover(v[L]);

        std::cout << "\t\x1b[31mans -> \x1b[0m" << std::boolalpha << ans
            << std::endl << std::endl;
    }

    return 0;
}
