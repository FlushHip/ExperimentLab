#include "headers.h"

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < 32; ++i) {
            int sum = 0;
            for (int j = 0; j < nums.size(); ++j) {
                sum += (nums[j] & (1 << i)) != 0;
            }
            ans |= sum % 3 ? 1 << i : 0;
        }
        return ans;
    }
};
