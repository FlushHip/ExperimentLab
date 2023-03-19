#include "headers.h"

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int index = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                std::swap(nums[i], nums[index++]);
            }
        }
        for (int i = index; i < n; ++i) {
            if (nums[i] == 1) {
                std::swap(nums[i], nums[index++]);
            }
        }
    }
};
