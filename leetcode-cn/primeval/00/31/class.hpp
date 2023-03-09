#include "headers.h"

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        std::vector<std::vector<int>> ans;
        int index = n - 1;
        while (index - 1 >= 0 && nums[index - 1] >= nums[index]) {
            --index;
        }
        if (index == 0) {
            std::reverse(nums.begin(), nums.end());
            return;
        }
        int pos = n - 1;
        while (nums[pos] <= nums[index - 1]) {
            --pos;
        }
        std::swap(nums[index - 1], nums[pos]);
        std::reverse(nums.begin() + index, nums.end());
    }
};
