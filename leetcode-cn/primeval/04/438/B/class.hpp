#include "headers.h"

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.size() < p.size()) {
            return {};
        }
        constexpr unsigned int line_length = 26;
        std::array<int, line_length> line{0};
        for (auto i = 0U; i < p.size(); ++i) {
            ++line[s[i] - 'a'];
            --line[p[i] - 'a'];
        }
        auto diff = std::count_if(
            line.begin(), line.end(), [](int i) { return i != 0; });
        std::vector<int> ans;
        for (int index = 0;; ++index) {
            if (diff == 0) {
                ans.push_back(index);
            }
            if (index + p.size() + 1 <= s.size()) {
                --line[s[index] - 'a'];
                if (line[s[index] - 'a'] == -1) {
                    ++diff;
                }
                if (line[s[index] - 'a'] == 0) {
                    --diff;
                }

                ++line[s[index + p.size()] - 'a'];
                if (line[s[index + p.size()] - 'a'] == 1) {
                    ++diff;
                }
                if (line[s[index + p.size()] - 'a'] == 0) {
                    --diff;
                }
            } else {
                break;
            }
        }
        return ans;
    }
};
