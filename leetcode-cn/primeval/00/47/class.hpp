#include "headers.h"

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int n = nums.size();
        std::vector<std::vector<int>> ans;
        std::sort(nums.begin(), nums.end());
        while (true) {
            ans.emplace_back(nums);
            int index = n - 1;
            while (index - 1 >= 0 && nums[index - 1] >= nums[index]) {
                --index;
            }
            if (index == 0) {
                break;
            }
            int pos = n - 1;
            while (nums[pos] <= nums[index - 1]) {
                --pos;
            }
            std::swap(nums[index - 1], nums[pos]);
            std::reverse(nums.begin() + index, nums.end());
        }
        return ans;
    }
};
