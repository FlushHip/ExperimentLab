#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VList<std::pair<int, int>> v{
        {4, 2},
        {5, 3},
        {1, 1},
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :" << std::endl;

        std::cout << "\t\x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto ans = sol->combine(v[L].first, v[L].second);

        std::cout << "\t\x1b[31mans -> \x1b[0m" << ans << std::endl
                  << std::endl;
    }

    return 0;
}
