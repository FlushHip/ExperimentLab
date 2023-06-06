#include "headers.h"

class Solution {
public:
    int maxRepOpt1(string text) {
        std::vector<std::pair<char, int>> line;
        std::unordered_map<char, int> cnt;
        for (char pre_c = 0; char c : text) {
            if (pre_c != c) {
                line.emplace_back(c, 1);
            } else {
                ++line.back().second;
            }
            pre_c = c;
            ++cnt[c];
        }

        int ans = std::max_element(
            line.begin(), line.end(), [](auto&& lhs, auto&& rhs) {
                return lhs.second < rhs.second;
            })->second;
        for (auto&& [c, num] : line) {
            if (cnt[c] - num > 0) {
                ans = std::max(ans, num + 1);
            }
        }
        for (unsigned int i = 0U; i < line.size(); ++i) {
            if (line[i].second == 1 && i != 0 && i != line.size() - 1 &&
                line[i - 1].first == line[i + 1].first) {
                int num = line[i - 1].second + line[i + 1].second;
                if (cnt[line[i - 1].first] - num > 0) {
                    ++num;
                }
                ans = std::max(ans, num);
            }
        }
        return ans;
    }
};
