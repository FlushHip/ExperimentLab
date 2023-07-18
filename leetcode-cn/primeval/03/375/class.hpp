#include "headers.h"

class Solution {
public:
    int getMoneyAmount(int n) {
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
        for (int L = 2; L <= n; ++L) {
            for (int i = 1; i + L - 1 <= n; ++i) {
                dp[i][i + L - 1] = i + L - 1 + dp[i][i + L - 1 - 1];
                for (int x = i; x < i + L - 1; ++x) {
                    dp[i][i + L - 1] = std::min(dp[i][i + L - 1],
                        x + std::max(dp[i][x - 1], dp[x + 1][i + L - 1]));
                }
            }
        }
        return dp[1][n];
    }
};
