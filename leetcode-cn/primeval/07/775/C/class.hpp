#include "headers.h"

class Solution {
public:
    bool isIdealPermutation(vector<int>& nums) {
        int pre_max = -1;
        for (int i = 2; i < nums.size(); ++i) {
            pre_max = std::max(pre_max, nums[i - 2]);
            if (pre_max > nums[i]) {
                return false;
            }
        }
        return true;
    }
};
