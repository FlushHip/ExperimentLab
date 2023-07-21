#include "headers.h"

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = static_cast<int>(nums.size()), sum = 0;
        std::vector<int> dp(n), max_lhs(n);
        dp[0] = max_lhs[0] = sum = nums[0];
        for (int i = 1; i < n; ++i) {
            dp[i] = std::max(dp[i - 1] + nums[i], nums[i]);
            max_lhs[i] = std::max(max_lhs[i - 1], sum += nums[i]);
        }
        int ans_1 = *std::max_element(dp.begin(), dp.end());
        int ans_2 = std::numeric_limits<int>::min();
        sum = 0;
        for (int i = n - 1; i > 0; --i) {
            sum += nums[i];
            ans_2 = std::max(ans_2, sum + max_lhs[i - 1]);
        }
        return std::max(ans_1, ans_2);
    }
};
