#include "headers.h"

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        int result = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1] && ++result != i) {
                nums[result] = nums[i];
            }
        }
        return ++result;
    }
};
