#include "headers.h"

class Solution {
public:
    int numTilings(int n) {
        if (n < 3) {
            return n;
        }
        constexpr long long mod = 1e9 + 7;
        std::array<std::array<long long, 3>, 3> dp;
        dp[0] = {0, 0, 1};
        dp[1] = {1, 1, 2};
        for (int i = 2; i < n; ++i) {
            dp[index(i)][0] = dp[index(i - 2)][2] + dp[index(i - 1)][1];
            dp[index(i)][1] = dp[index(i - 2)][2] + dp[index(i - 1)][0];
            dp[index(i)][2] = dp[index(i - 1)][2] + dp[index(i - 2)][2] +
                dp[index(i - 1)][0] + dp[index(i - 1)][1];
            for (int j = 0; j < dp[index(i)].size(); ++j) {
                dp[index(i)][j] %= mod;
            }
        }
        return dp[index(n - 1)][2];
    }

private:
    inline int index(int i) { return i % 3; };
};
