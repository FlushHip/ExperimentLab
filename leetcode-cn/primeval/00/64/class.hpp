#include <limits>
#include "headers.h"

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dp[i][j] = grid[i][j] +
                    (i == 0 && j == 0
                            ? 0
                            : std::min(
                                  (i - 1 < 0 ? std::numeric_limits<int>::max()
                                             : dp[i - 1][j]),
                                  (j - 1 < 0 ? std::numeric_limits<int>::max()
                                             : dp[i][j - 1])));
            }
        }
        return dp[n - 1][m - 1];
    }
};
