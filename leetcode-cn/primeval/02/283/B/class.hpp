#include "headers.h"

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        for (int lhs = 0, rhs = 0; rhs < n; ++rhs) {
            if (nums[rhs]) {
                if (rhs != lhs) {
                    std::swap(nums[lhs], nums[rhs]);
                }
                ++lhs;
            }
        }
    }
};
