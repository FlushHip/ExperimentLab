#include "headers.h"

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = static_cast<int>(intervals.size());
        std::sort(intervals.begin(), intervals.end(),
            [](const auto& lhs, const auto& rhs) { return lhs[1] < rhs[1]; });
        std::vector<int> dp(n, 0);
        dp[0] = 1;
        for (int i = 1; i < n; ++i) {
            dp[i] = dp[i - 1];
            auto it = std::upper_bound(intervals.begin(), intervals.begin() + i,
                intervals[i][0],
                [](int lhs, const auto& rhs) { return lhs < rhs[1]; });
            if (it != intervals.begin()) {
                dp[i] =
                    std::max(dp[i], 1 + dp[std::prev(it) - intervals.begin()]);
            } else {
                dp[i] = std::max(dp[i], 1);
            }
        }
        return n - dp[n - 1];
    }
};
