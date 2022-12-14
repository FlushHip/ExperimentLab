#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VTList<int, std::vector<std::vector<int>>, std::vector<std::vector<int>>> v{
        {
            3,
            {
                {0, 1, 2},
                {1, 2, 4},
                {2, 0, 8},
                {1, 0, 16},
            },
            {
                {0, 1, 2},
                {0, 2, 5},
            },
        },
        {
            5,
            {
                {0, 1, 10},
                {1, 2, 5},
                {2, 3, 9},
                {3, 4, 13},
            },
            {
                {0, 4, 14},
                {1, 4, 13},
            },
        },
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->distanceLimitedPathsExist(UNPACK_3(v[L]));

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            (std::chrono::steady_clock::now() - start_epoch) * 1000);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m" << std::boolalpha << ans
                  << std::endl
                  << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                  << duration.count() << "ms\x1b[0m" << std::endl
                  << std::endl;
    }

    return 0;
}
