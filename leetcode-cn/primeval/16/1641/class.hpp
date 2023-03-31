#include "headers.h"

class Solution {
public:
    int countVowelStrings(int n) {
        std::vector<std::array<int, 5>> dp(n);
        dp[0] = {1, 1, 1, 1, 1};
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 5; ++j) {
                dp[i][j] = 0;
                for (int k = 0; k <= j; ++k) {
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }
        return std::accumulate(dp[n - 1].begin(), dp[n - 1].end(), 0);
    }
};
