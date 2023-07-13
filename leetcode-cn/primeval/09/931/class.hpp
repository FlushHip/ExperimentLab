#include "headers.h"

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = static_cast<int>(matrix.size()),
            m = static_cast<int>(matrix[0].size());
        std::array<std::vector<int>, 2> dp;
        dp.fill(matrix[0]);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dp[i % 2][j] = matrix[i][j] +
                    std::min({dp[(i - 1) % 2][j],
                        j - 1 >= 0 ? dp[(i - 1) % 2][j - 1]
                                   : std::numeric_limits<int>::max(),
                        j + 1 < m ? dp[(i - 1) % 2][j + 1]
                                  : std::numeric_limits<int>::max()});
            }
        }
        return *std::min_element(
            dp[(n - 1) % 2].begin(), dp[(n - 1) % 2].end());
    }
};
