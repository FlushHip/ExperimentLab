#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VList<std::vector<std::string>> v{
        {"A", "1", "B", "C", "D", "2", "3", "4", "E", "5", "F", "G", "6", "7",
            "H", "I", "J", "K", "L", "M"},
        {"A", "A"},
        {"42", "10", "O", "t", "y", "p", "g", "B", "96", "H", "5", "v", "P",
            "52", "25", "96", "b", "L", "Y", "z", "d", "52", "3", "v", "71",
            "J", "A", "0", "v", "51", "E", "k", "H", "96", "21", "W", "59", "I",
            "V", "s", "59", "w", "X", "33", "29", "H", "32", "51", "f", "i",
            "58", "56", "66", "90", "F", "10", "93", "53", "85", "28", "78",
            "d", "67", "81", "T", "K", "S", "l", "L", "Z", "j", "5", "R", "b",
            "44", "R", "h", "B", "30", "63", "z", "75", "60", "m", "61", "a",
            "5", "S", "Z", "D", "2", "A", "W", "k", "84", "44", "96", "96", "y",
            "M"},
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->findLongestSubarray(v[L]);

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
