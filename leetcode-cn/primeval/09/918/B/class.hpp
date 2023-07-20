#include "headers.h"

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::vector<int> dp_max(n), dp_min(n);
        dp_max[0] = dp_min[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            dp_max[i] = std::max(dp_max[i - 1] + nums[i], nums[i]);
            dp_min[i] = std::min(dp_min[i - 1] + nums[i], nums[i]);
        }
        auto ans_max = *std::max_element(dp_max.begin(), dp_max.end());
        if (ans_max < 0) {
            return ans_max;
        }
        return std::max(ans_max,
            std::accumulate(nums.begin(), nums.end(), 0) -
                *std::min_element(dp_min.begin(), dp_min.end()));
    }
};
