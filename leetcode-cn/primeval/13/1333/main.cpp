#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VTList<std::vector<std::vector<int>>, int, int, int> v{
        {
            {
                {1, 4, 1, 40, 10},
                {2, 8, 0, 50, 5},
                {3, 8, 1, 30, 4},
                {4, 10, 0, 10, 3},
                {5, 1, 1, 15, 1},
            },
            1,
            50,
            10,
        },
        {
            {
                {1, 4, 1, 40, 10},
                {2, 8, 0, 50, 5},
                {3, 8, 1, 30, 4},
                {4, 10, 0, 10, 3},
                {5, 1, 1, 15, 1},
            },
            0,
            50,
            10,
        },
        {
            {
                {1, 4, 1, 40, 10},
                {2, 8, 0, 50, 5},
                {3, 8, 1, 30, 4},
                {4, 10, 0, 10, 3},
                {5, 1, 1, 15, 1},
            },
            0,
            30,
            3,
        },
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->filterRestaurants(UNPACK_4(v[L]));

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
