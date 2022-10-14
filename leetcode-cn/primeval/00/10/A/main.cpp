#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::pair<std::string, std::string>> v{
        {"bccbbabcaccacbcacaa", ".*b.*c*.*.*.c*a*.c"},
        {"abcaaaaaaabaabcabac", ".*ab.a.*a*a*.*b*b*"},
        {"a", "ab*"},
        {"a", "a.*"},
        {"a", "b*"},
        {"a", ".*"},
        {"aaa", "ab*a"},
        {"aaa", "ab*a*c*a"},
        {"aaa", "ab*ac*a"},
        {"aa", "a"},
        {"aa", "a*"},
        {"ab", ".*"},
        {"asfsfs", ".*s"},
        {"aaabbbccca", ".*b*c*a"},
        {"aaabbbccca", ".*b*c*"},
        {"aab", "c*a*b"},
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->isMatch(v[L].first, v[L].second);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                            (std::chrono::steady_clock::now() - start_epoch);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m"
            << std::boolalpha << ans << std::endl
            << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                << duration.count() << "ms\x1b[0m"
            << std::endl << std::endl;
    }

    return 0;
}
