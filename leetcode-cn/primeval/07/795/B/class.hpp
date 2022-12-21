#include "headers.h"

class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int n = nums.size(), ans = 0;
        int lhs = -1, rhs = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] >= left && nums[i] <= right) {
                rhs = i;
            } else if (nums[i] > right) {
                lhs = i;
                rhs = -1;
            }
            if (rhs != -1) {
                ans += rhs - lhs;
            }
        }
        return ans;
    }
};
