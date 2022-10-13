#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<int> v{
        6,
        8,
        14,
        1,
        0,
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :" << std::endl;

        std::cout << "\t\x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto ans = sol->isUgly(v[L]);

        std::cout << "\t\x1b[31mans -> \x1b[0m" << std::boolalpha << ans
            << std::endl << std::endl;
    }

    return 0;
}
