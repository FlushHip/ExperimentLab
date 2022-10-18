#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VTList<std::vector<std::string>, int> v{
        {{"1", "3", "5", "7"}, 100},
        {{"1", "4", "9"}, 1000000000},
        {{"1", "4", "9"}, 999999999},
        {{"1", "4", "9"}, 999999998},
        {{"1", "4", "9"}, 999999997},
        {{"1", "4", "9"}, 999999994},
        {{"1", "4", "9"}, 999999993},
        {{"7"}, 8},
        {{"7"}, 7},
        {{"7"}, 6},
        {{"5", "6"}, 19},
        {{"5", "7", "8"}, 59},
        {{"5", "7", "8"}, 58},
        {{"5", "7", "8"}, 57},
        {{"5", "7", "8"}, 56},
        {{"5", "7", "8"}, 55},
        {{"5", "7", "8"}, 54},
        {{"1"}, 834},
        {{"1"}, 831},
        {{"2"}, 832},
        {{"3"}, 832},
        {{"3"}, 811},
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans =
            sol->atMostNGivenDigitSet(std::get<0>(v[L]), std::get<1>(v[L]));

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
