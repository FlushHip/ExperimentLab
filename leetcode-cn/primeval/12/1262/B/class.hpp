#include "headers.h"

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int n = nums.size();
        std::vector<std::array<int, 3>> dp(n);
        dp[0] = {0};
        dp[0][nums[0] % 3] = nums[0];
        for (int i = 1; i < n; ++i) {
            int m = nums[i] % 3;
            dp[i][0] = std::max(dp[i - 1][0],
                dp[i - 1][(3 - m) % 3] ? dp[i - 1][(3 - m) % 3] + nums[i]
                    : m == 0           ? nums[i]
                                       : 0);
            dp[i][1] = std::max(dp[i - 1][1],
                dp[i - 1][(4 - m) % 3] ? dp[i - 1][(4 - m) % 3] + nums[i]
                    : m == 1           ? nums[i]
                                       : 0);
            dp[i][2] = std::max(dp[i - 1][2],
                dp[i - 1][(5 - m) % 3] ? dp[i - 1][(5 - m) % 3] + nums[i]
                    : m == 2           ? nums[i]
                                       : 0);
        }
        return dp[n - 1][0];
    }
};
