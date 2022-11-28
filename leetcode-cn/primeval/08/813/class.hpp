#include "headers.h"

class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<int> sums;
        std::partial_sum(nums.begin(), nums.end(), std::back_inserter(sums));
        Dp dp(n, std::vector<double>(1 + k, -1));
        return dfs(n - 1, k, dp, sums);
    }

private:
    using Dp = std::vector<std::vector<double>>;
    double dfs(int i, int x, Dp& dp, const std::vector<int> sums) {
        if (dp[i][x] != -1) {
            return dp[i][x];
        }

        double ans = 1.0 * sums[i] / (i + 1);
        if (i == 0) {
            return ans;
        }

        for (int ii = i - 1; x - 1 > 0 && ii >= 0; --ii) {
            ans = std::max(ans,
                dfs(ii, x - 1, dp, sums) +
                    (0.0 + sums[i] - sums[ii]) / (i - ii));
        }

        return dp[i][x] = ans;
    }
};
