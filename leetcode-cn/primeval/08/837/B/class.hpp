#include "headers.h"

class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        if (k == 0) {
            return 1;
        }
        int top = std::min(n, k + maxPts - 1);
        std::vector<double> dp(top + 1);
        std::vector<double> sum(top + 1);
        dp[0] = 1;
        sum[0] = dp[0];
        for (int i = 1; i <= k - 1; ++i) {
            dp[i] =
                (sum[i - 1] - (i - maxPts - 1 >= 0 ? sum[i - maxPts - 1] : 0)) /
                maxPts;
            sum[i] = sum[i - 1] + dp[i];
        }
        double ans = 0;
        for (int i = k; i <= top; ++i) {
            ans +=
                (sum[k - 1] - (i - maxPts - 1 >= 0 ? sum[i - maxPts - 1] : 0)) /
                maxPts;
        }
        return ans;
    }
};
