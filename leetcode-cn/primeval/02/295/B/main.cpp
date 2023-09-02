#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    VList<std::vector<int>> v{
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {2, 1, 9, 10, 5, 6, 3, 7, 8, 4},
        {40, 12, 16, 14},
    };

    for (auto L = 0U; L < v.size(); ++L) {
        auto sol = std::make_unique<MedianFinder>();

        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        std::vector<double> ans;
        for (auto val : v[L]) {
            sol->addNum(val);
            ans.emplace_back(sol->findMedian());
        }

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
