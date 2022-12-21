#include "headers.h"

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(m));
        for (int i = 0; i < n; ++i) {
            dp[i][0] = matrix[i][0] == '1';
        }
        for (int j = 0; j < m; ++j) {
            dp[0][j] = matrix[0][j] == '1';
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                dp[i][j] = matrix[i][j] == '0'
                    ? 0
                    : std::min({dp[i - 1][j], dp[i - 1][j - 1], dp[i][j - 1]}) +
                        1;
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans = std::max(ans, dp[i][j]);
            }
        }
        return ans * ans;
    }
};
