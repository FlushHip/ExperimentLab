#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::pair<std::vector<int>, int>> v{
        {{6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12}, 2},
        {{3, 3, 3, 3, 3}, 3},
        {{7, 6, 5, 4, 3, 2, 1}, 1},
        {{7, 1, 7, 1, 7, 1}, 2},
        {{66}, 1},
        {{1, 2, 3, 4, 5}, 1},
        {{5, 4, 3, 2, 1}, 1},
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->maxJumps(v[L].first, v[L].second);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                            (std::chrono::steady_clock::now() - start_epoch);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m"
            << std::boolalpha << ans << std::endl
            << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                << duration.count() << "ms\x1b[0m"
            << std::endl << std::endl;
    }

    return 0;
}
