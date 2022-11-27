#include "headers.h"

class Solution {
public:
    bool check(vector<int>& nums) {
        int n = nums.size();
        int lhs = 0;
        for (; lhs + 1 < n && nums[lhs] <= nums[lhs + 1]; ++lhs) {
        }
        if (lhs + 1 == n) {
            return true;
        }
        int rhs = lhs + 1;
        for (; rhs + 1 < n && nums[rhs] <= nums[rhs + 1]; ++rhs) {
        }
        return rhs + 1 == n && (nums.back() <= nums.front());
    }
};
