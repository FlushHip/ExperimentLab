#include "headers.h"

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::array<std::vector<long long>, 2> dp;
        dp.fill(std::vector<long long>(n));
        dp[0][0] = 0;
        dp[1][0] = nums[0];
        for (int i = 1; i < n; ++i) {
            dp[0][i] = std::max(dp[0][i - 1], dp[1][i - 1] - nums[i]);
            dp[1][i] = std::max(dp[1][i - 1], dp[0][i - 1] + nums[i]);
        }
        return std::max(dp[0].back(), dp[1].back());
    }
};
