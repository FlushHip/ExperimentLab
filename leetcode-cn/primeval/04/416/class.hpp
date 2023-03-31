#include "headers.h"

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int target = std::accumulate(nums.begin(), nums.end(), 0);
        if (target % 2) {
            return false;
        }
        target >>= 1;

        std::vector<int> dp(target + 1, false);
        dp[0] = true;
        for (int i = 0; i < n; ++i) {
            for (int num = target; num - nums[i] >= 0; --num) {
                if (dp[num]) {
                    continue;
                }
                dp[num] = dp[num - nums[i]];
            }
            if (dp[target]) {
                return true;
            }
        }
        return false;
    }
};
