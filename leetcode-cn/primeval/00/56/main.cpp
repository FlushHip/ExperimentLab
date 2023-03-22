#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VList<std::vector<std::vector<int>>> v{
        {
            {1, 3},
            {2, 6},
            {8, 10},
            {15, 18},
        },
        {
            {1, 4},
            {4, 5},
        },
        {
            {1, 1},
            {1, 1},
            {1, 1},
            {1, 1},
            {1, 1},
            {1, 1},
            {-1, 10},
            {9, 10},
            {8, 11},
            {53, 353},
        },
        {

            {2, 3},
            {4, 5},
            {6, 7},
            {8, 9},
            {1, 10},
        },
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->merge(v[L]);

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