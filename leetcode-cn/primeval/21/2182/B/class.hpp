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
        for (int last = alpha_length - 1, second_last = last - 1, sum = 0;
             last >= 0 && second_last >= 0;) {
            if (0 == line[last]) {
                --last;
                sum = 0;
            } else if (sum < repeatLimit) {
                ++sum;
                --line[last];
                ret.push_back(last + 'a');
            } else if (second_last >= last || 0 == line[second_last]) {
                --second_last;
            } else {
                line[second_last] -= 1;
                ret.push_back(second_last + 'a');
                sum = 0;
            }
        }
        return ret;
    }
};
