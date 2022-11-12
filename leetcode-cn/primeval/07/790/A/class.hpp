#include "headers.h"

class Solution {
public:
    int numTilings(int n) {
        if (n < 3) {
            return n;
        }
        constexpr long long mod = 1e9 + 7;
        std::vector<std::array<long long, 3>> dp(n);
        dp[0] = {0, 0, 1};
        dp[1] = {1, 1, 2};
        for (int i = 2; i < n; ++i) {
            dp[i][0] = dp[i - 2][2] + dp[i - 1][1];
            dp[i][1] = dp[i - 2][2] + dp[i - 1][0];
            dp[i][2] =
                dp[i - 1][2] + dp[i - 2][2] + dp[i - 1][0] + dp[i - 1][1];
            for (int j = 0; j < dp[i].size(); ++j) {
                dp[i][j] %= mod;
            }
        }
        return dp[n - 1][2];
    }
};
