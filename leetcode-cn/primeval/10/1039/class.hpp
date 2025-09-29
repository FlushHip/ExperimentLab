#include "headers.h"

class Solution {
private:
    int dfs(const std::vector<int>& values,
        std::vector<std::vector<int>>& dp,
        int lhs,
        int rhs) {
        if (0 != dp[lhs][rhs - 1]) {
            return dp[lhs][rhs - 1];
        }
        if (rhs - lhs == 3) {
            return dp[lhs][rhs - 1] =
                       values[lhs] * values[lhs + 1] * values[lhs + 2];
        }
        if (rhs - lhs < 3) {
            return 0;
        }
        int result = std::numeric_limits<int>::max();
        for (int i = lhs + 1; i + 1 < rhs; ++i) {
            int sum = values[lhs] * values[rhs - 1] * values[i] +
                dfs(values, dp, lhs, i + 1) + dfs(values, dp, i, rhs);
            result = std::min(result, sum);
        }
        return dp[lhs][rhs - 1] = result;
    }

public:
    int minScoreTriangulation(vector<int>& values) {
        int n = static_cast<int>(values.size());
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        int ans = dfs(values, dp, 0, n);
        return ans;
    }
};