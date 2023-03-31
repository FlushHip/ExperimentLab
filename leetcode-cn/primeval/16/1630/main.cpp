#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VTList<std::vector<int>, std::vector<int>, std::vector<int>> v{
        {
            {4, 6, 5, 9, 3, 7},
            {0, 0, 2},
            {2, 3, 5},
        },
        {
            {-12, -9, -3, -12, -6, 15, 20, -25, -20, -15, -10},
            {0, 1, 6, 4, 8, 7},
            {4, 4, 9, 7, 9, 10},
        },
        {
            {-3, -6, -8, -4, -2, -8, -6, 0, 0, 0, 0},
            {5, 4, 3, 2, 4, 7, 6, 1, 7},
            {6, 5, 6, 3, 7, 10, 7, 4, 10},
        }};

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->checkArithmeticSubarrays(UNPACK_3(v[L]));

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
