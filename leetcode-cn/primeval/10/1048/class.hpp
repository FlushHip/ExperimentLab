#include "headers.h"

class Solution {
public:
    int longestStrChain(vector<string>& words) {
        std::sort(words.begin(), words.end(),
            [](std::string_view lhs, std::string_view rhs) {
                return lhs.size() < rhs.size();
            });
        int n = static_cast<int>(words.size());
        std::vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i) {
            int j = i - 1;
            for (; j >= 0 && words[j].size() == words[i].size(); --j) {
            }
            for (; j >= 0 && words[j].size() + 1 == words[i].size(); --j) {
                unsigned int ii = 0, jj = 0;
                for (; ii < words[i].size() && jj < words[j].size();) {
                    if (words[i][ii] == words[j][jj]) {
                        ++jj;
                    }
                    ++ii;
                }
                if (jj == words[j].size()) {
                    dp[i] = std::max(dp[j] + 1, dp[i]);
                }
            }
        }
        return *std::max_element(dp.begin(), dp.end());
    }
};
