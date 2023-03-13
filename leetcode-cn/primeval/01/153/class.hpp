#include "headers.h"

class Solution {
public:
    int findMin(vector<int>& nums) {
        int lhs = 0, rhs = nums.size() - 1;
        while (lhs < rhs) {
            if (nums[lhs] <= nums[rhs]) {
                return nums[lhs];
            }
            if (rhs - lhs == 1) {
                return nums[rhs];
            }
            int mid = (lhs + rhs) / 2;
            if (nums[lhs] > nums[mid]) {
                rhs = mid;
            } else {
                lhs = mid;
            }
        }
        return nums[lhs];
    }
};
