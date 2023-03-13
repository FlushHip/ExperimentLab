#include "headers.h"

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int ans = 0, n = nums.size();
        std::vector<int> dp;
        dp.push_back(nums.front());
        for (int i = 1; i < n; ++i) {
            if (nums[i] > dp.back()) {
                dp.push_back(nums[i]);
            } else {
                int lhs = -1, rhs = dp.size() - 1;
                while (lhs < rhs) {
                    int mid = (lhs + rhs + 1) / 2;
                    if (nums[i] <= dp[mid]) {
                        rhs = mid - 1;
                    } else {
                        lhs = mid;
                    }
                }
                dp[rhs + 1] = nums[i];
            }
        }
        return dp.size();
    }
};
