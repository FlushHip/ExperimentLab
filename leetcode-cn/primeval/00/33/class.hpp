#include "headers.h"

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lhs = 0, rhs = nums.size() - 1;
        while (lhs <= rhs) {
            int mid = (lhs + rhs) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            if ((nums[lhs] <= nums[mid] && nums[lhs] <= target &&
                    target < nums[mid]) ||
                (nums[mid] <= nums[rhs] &&
                    !(nums[mid] < target && target <= nums[rhs]))) {
                rhs = mid - 1;
            } else {
                lhs = mid + 1;
            }
        }
        return -1;
    }
};
