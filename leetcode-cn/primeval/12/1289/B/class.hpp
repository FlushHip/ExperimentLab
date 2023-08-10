#include "headers.h"

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        auto dp = grid;
        // TODO(flushhip): optimize
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i][j] = std::numeric_limits<int>::max();
                for (int k = 0; k < n; ++k) {
                    if (j != k) {
                        dp[i][j] =
                            std::min(dp[i][j], dp[i - 1][k] + grid[i][j]);
                    }
                }
            }
        }
        return *std::min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};
