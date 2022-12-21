#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VTList<std::vector<std::vector<int>>, int, int> v{
        {
            {
                {0, 1, 10},
                {0, 2, 1},
                {1, 2, 2},
            },
            6,
            3,
        },
        {
            {
                {0, 1, 4},
                {1, 2, 6},
                {0, 2, 8},
                {1, 3, 1},
            },
            10,
            4,
        },
        {{
             {1, 2, 4},
             {1, 4, 5},
             {1, 3, 1},
             {2, 3, 4},
             {3, 4, 5},
         },
            17, 5},
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->reachableNodes(UNPACK_3(v[L]));

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
