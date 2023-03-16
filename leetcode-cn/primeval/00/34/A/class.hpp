#include "headers.h"

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        std::vector<int> ans(2);
        int lhs = 0, rhs = n;
        while (lhs < rhs) {
            int mid = (lhs + rhs) / 2;
            if (nums[mid] < target) {
                lhs = mid + 1;
            } else {
                rhs = mid;
            }
        }
        ans[0] = lhs == n ? -1 : nums[lhs] == target ? lhs : -1;

        lhs = -1, rhs = n - 1;
        while (lhs < rhs) {
            int mid = (lhs + rhs + 1) / 2;
            if (nums[mid] > target) {
                rhs = mid - 1;
            } else {
                lhs = mid;
            }
        }
        ans[1] = rhs != -1 ? nums[rhs] == target ? rhs : -1 : -1;

        return ans;
    }
};
