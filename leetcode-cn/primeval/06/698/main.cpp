#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VList<std::pair<std::vector<int>, int>> v{
        {{1, 1, 1}, 3},
        {{4, 3, 2, 3, 5, 2, 1}, 4},
        {{1, 2, 3, 4}, 3},
        {{1, 2, 3, 4, 5, 6, 7}, 1},
        {{1, 2, 3, 4, 5, 6, 7}, 2},
        {{960, 3787, 1951, 5450, 4813, 752, 1397, 801, 1990, 1095, 3643, 8133,
             893, 5306, 8341, 5246},
            6},
        {{2, 9, 4, 7, 3, 2, 10, 5, 3, 6, 6, 2, 7, 5, 2, 4}, 7},
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->canPartitionKSubsets(v[L].first, v[L].second);

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
