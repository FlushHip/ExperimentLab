#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VTList<std::string, std::vector<std::string>> v{
        {"abcde",
            {
                "a",
                "bb",
                "acd",
                "ace",
            }},
        {"dsahjpjauf",
            {
                "ahjpjau",
                "ja",
                "ahbwzgqnuk",
                "tnmlanowax",
            }},
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        // auto ans = aux::call(&Solution::numMatchingSubseq, sol, v[L]);
        auto ans = sol->numMatchingSubseq(UNPACK_2(v[L]));

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
