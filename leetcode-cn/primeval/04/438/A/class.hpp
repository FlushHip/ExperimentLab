#include "headers.h"

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.size() < p.size()) {
            return {};
        }
        constexpr unsigned int line_length = 26;
        auto fn = [](std::string_view str) -> std::array<int, line_length> {
            std::array<int, line_length> ret{0};
            for (char c : str) {
                ++ret[c - 'a'];
            }
            return ret;
        };
        auto target = fn(p), line = fn({s.data(), p.size()});
        std::vector<int> ans;
        for (int index = 0;; ++index) {
            if (target == line) {
                ans.push_back(index);
            }
            if (index + p.size() + 1 <= s.size()) {
                --line[s[index] - 'a'];
                ++line[s[index + p.size()] - 'a'];
            } else {
                break;
            }
        }
        return ans;
    }
};
