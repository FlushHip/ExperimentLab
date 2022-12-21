#include "headers.h"

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
        dp[0][0] = 1 ^ obstacleGrid[0][0];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i == 0 && j == 0) || obstacleGrid[i][j]) {
                    continue;
                }
                dp[i][j] = (j - 1 < 0 ? 0 : dp[i][j - 1]) +
                    (i - 1 < 0 ? 0 : dp[i - 1][j]);
            }
        }
        return dp[n - 1][m - 1];
    }
};
