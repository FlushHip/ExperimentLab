#include "headers.h"

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int index_0 = 0, index_2 = n - 1;
        for (int i = 0; i <= index_2; ++i) {
            while (nums[i] == 2 && i < index_2) {
                std::swap(nums[i], nums[index_2--]);
            }
            if (nums[i] == 0) {
                std::swap(nums[i], nums[index_0++]);
            }
        }
    }
};
