#include <string_view>
#include "headers.h"

class Solution {
public:
    bool halvesAreAlike(string s) {
        auto fun = [](std::string_view str) -> int {
            constexpr std::string_view alphas{"aeiou"};
            return std::count_if(str.begin(), str.end(), [alphas](char c) {
                c = std::tolower(c);
                return std::any_of(alphas.begin(), alphas.end(),
                    [c](char cc) { return cc == c; });
            });
        };
        return fun({s.data(), s.size() / 2}) ==
            fun({s.data() + s.size() / 2, s.size() / 2});
    }
};
