#include <algorithm>
#include "headers.h"

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int max_ele = *std::max_element(nums.begin(), nums.end());
        int sum = 0, ans = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == max_ele) {
                ++sum;
                ans = std::max(ans, sum);
            } else {
                sum = 0;
            }
        }
        return ans;
    }
};
