#include "headers.h"

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int index_0 = 0, index_1 = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 1) {
                std::swap(nums[i], nums[index_1++]);
            } else if (nums[i] == 0) {
                std::swap(nums[i], nums[index_0]);
                if (index_0 != index_1) {
                    std::swap(nums[i], nums[index_1]);
                }
                ++index_0;
                ++index_1;
            }
        }
    }
};
