#include "headers.h"

class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0) - x;
        if (sum < 0) {
            return -1;
        }
        int lhs = 0, rhs = 0, res = 0, ans = -1;
        while (lhs <= rhs && rhs <= nums.size()) {
            if (sum < res) {
                res -= nums[lhs];
                ++lhs;
            } else {
                if (sum == res) {
                    ans = std::max(ans, rhs - lhs);
                }
                if (rhs < nums.size()) {
                    res += nums[rhs];
                }
                ++rhs;
            }
        }
        return ans == -1 ? -1 : nums.size() - ans;
    }
};
