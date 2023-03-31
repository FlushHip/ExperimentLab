#include "headers.h"

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::vector<int> dp_max(n), dp_min(n);
        dp_max[0] = dp_min[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > 0) {
                dp_max[i] = std::max(nums[i], dp_max[i - 1] * nums[i]);
                dp_min[i] = std::min(nums[i], dp_min[i - 1] * nums[i]);
            } else {
                dp_max[i] = std::max(nums[i], dp_min[i - 1] * nums[i]);
                dp_min[i] = std::min(nums[i], dp_max[i - 1] * nums[i]);
            }
        }
        return *std::max_element(dp_max.begin(), dp_max.end());
    }
};
