#include "headers.h"

class Solution {
public:
    int uniquePaths(int m, int n) {
        std::vector<std::vector<int>> dp(m, std::vector<int>(n));
        std::fill_n(dp[0].begin(), n, 1);
        std::for_each(dp.begin(), dp.end(), [](auto& v) { v[0] = 1; });
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
