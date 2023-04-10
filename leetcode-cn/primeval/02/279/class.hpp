#include "headers.h"

class Solution {
public:
    int numSquares(int n) {
        std::vector<int> dp(n + 1);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = i;
            for (int kk = 1; kk * kk <= i; ++kk) {
                dp[i] = std::min(dp[i], dp[i - kk * kk] + 1);
            }
        }
        return dp[n];
    }
};
