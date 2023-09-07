#include "headers.h"

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = static_cast<int>(points.size());
        std::sort(points.begin(), points.end(),
            [](const auto& lhs, const auto& rhs) { return lhs[1] < rhs[1]; });
        std::vector<int> dp(n, 0);
        dp[0] = 1;
        for (int i = 1; i < n; ++i) {
            dp[i] = dp[i - 1];
            auto it = std::lower_bound(points.begin(), points.begin() + i,
                points[i][0],
                [](const auto& lhs, int rhs) { return lhs[1] < rhs; });
            if (it != points.begin()) {
                dp[i] = std::max(dp[i], 1 + dp[std::prev(it) - points.begin()]);
            } else {
                dp[i] = std::max(dp[i], 1);
            }
        }
        return dp[n - 1];
    }
};
