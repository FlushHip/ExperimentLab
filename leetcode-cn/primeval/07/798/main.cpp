#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::vector<int>> v{
        { 2, 3, 1, 4, 0 },
        { 1, 3, 0, 2, 4 },
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :" << std::endl;

        std::cout << "\t\x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto ans = sol->bestRotation(v[L]);

        std::cout << "\t\x1b[31mans -> \x1b[0m" << ans
            << std::endl << std::endl;
    }

    return 0;
}
