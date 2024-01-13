#include "headers.h"

class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        constexpr unsigned int alpha_length = 26;
        std::array<int, alpha_length> line{};
        for (const char c : s) {
            assert(std::islower(c));
            ++line[c - 'a'];
        }
        string ret;
        for (int last{}, sum{};;) {
            for (last = alpha_length - 1; last >= 0 &&
                 (line[last] == 0 ||
                     (sum != 0 && ret.back() - 'a' == last &&
                         sum == repeatLimit));
                 --last) {
            }
            if (last < 0) {
                break;
            }
            --line[last];
            if (sum != 0 && ret.back() - 'a' == last) {
                ++sum;
            } else {
                sum = 1;
            }
            ret.push_back(last + 'a');
        }
        return ret;
    }
};
