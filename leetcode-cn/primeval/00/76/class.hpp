#include "headers.h"

class Solution {
public:
    string minWindow(string s, string t) {
        constexpr int buff_length = 26 * 2;
        auto index = [](char c) {
            return std::islower(c) ? c - 'a' : 26 + c - 'A';
        };
        auto spec = [](const auto& a, const auto& b) {
            for (int i = 0; i < buff_length; ++i) {
                if (a[i] < b[i]) {
                    return false;
                }
            }
            return true;
        };
        std::array<int, buff_length> target{0}, line{0};
        for (char c : t) {
            ++target[index(c)];
        }

        int ans_value = std::numeric_limits<int>::max(), ans_begin = 0;
        for (int rhs = 0, lhs = 0; rhs < s.size(); ++rhs) {
            ++line[index(s[rhs])];
            while (spec(line, target)) {
                if (rhs - lhs + 1 < ans_value) {
                    ans_value = rhs - lhs + 1;
                    ans_begin = lhs;
                }

                --line[index(s[lhs])];
                ++lhs;
            }
        }
        return ans_value == std::numeric_limits<int>::max()
            ? ""
            : s.substr(ans_begin, ans_value);
    }
};
