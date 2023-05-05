#include "headers.h"

class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        int top = std::min(n, k + maxPts - 1);
        std::vector<double> dp(top + 1, -1);
        dp[0] = 1;
        double ans = 0;
        for (int i = k; i <= top; ++i) {
            for (int j = k - 1; j >= 0 && j >= i - maxPts; --j) {
                ans += 1.0 / maxPts * dfs(j, maxPts, dp);
            }
        }
        return ans == 0 ? 1 : ans;
    }

private:
    double dfs(int n, int maxPts, std::vector<double>& dp) {
        if (dp[n] != -1) {
            return dp[n];
        }
        double ret = 0;
        for (int i = 1; i <= maxPts && n - i >= 0; ++i) {
            ret += 1.0 / maxPts * dfs(n - i, maxPts, dp);
        }
        return dp[n] = ret;
    }
};
