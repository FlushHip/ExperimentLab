#include "headers.h"

class Solution {
public:
    int minSteps(int n) {
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n / 2 + 1, n));
        dp[1][0] = 0;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i / 3; ++j) {
                dp[i][j] = dp[i - j][j] + 1;
            }
            if (i % 2 == 0) {
                dp[i][i / 2] =
                    *std::min_element(dp[i / 2].begin(), dp[i / 2].end()) + 2;
            }
        }
        return *std::min_element(dp[n].begin(), dp[n].end());
    }
};
