#include "headers.h"

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = static_cast<int>(pairs.size());
        std::sort(pairs.begin(), pairs.end(),
            [](const auto& lhs, const auto& rhs) { return lhs[1] < rhs[1]; });
        std::vector<int> dp(n, 0);
        dp[0] = 1;
        for (int i = 1; i < n; ++i) {
            dp[i] = dp[i - 1];
            auto it =
                std::lower_bound(pairs.begin(), pairs.begin() + i, pairs[i][0],
                    [](const auto& lhs, int rhs) { return lhs[1] < rhs; });
            if (it != pairs.begin()) {
                dp[i] = std::max(dp[i], 1 + dp[std::prev(it) - pairs.begin()]);
            } else {
                dp[i] = std::max(dp[i], 1);
            }
        }
        return dp[n - 1];
    }
};
