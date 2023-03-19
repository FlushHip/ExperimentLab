#include "headers.h"

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = static_cast<int>(word1.size()),
            m = static_cast<int>(word2.size());
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = i;
        }
        for (int i = 1; i <= m; ++i) {
            dp[0][i] = i;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int op_insert = dp[i][j - 1] + 1;
                int op_delete = dp[i - 1][j] + 1;
                int op_repalce =
                    dp[i - 1][j - 1] + (word1[i - 1] != word2[j - 1]);
                dp[i][j] = std::min({op_insert, op_delete, op_repalce});
            }
        }
        return dp[n][m];
    }
};
