#include "headers.h"

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int n = static_cast<int>(nums.size());
        int ans = 0;
        for (int i = 0; i < n - 2; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                int sum = nums[i] + nums[j];
                auto it =
                    std::lower_bound(nums.begin() + j + 1, nums.end(), sum);
                ans += it - (nums.begin() + j + 1);
            }
        }
        return ans;
    }
};
