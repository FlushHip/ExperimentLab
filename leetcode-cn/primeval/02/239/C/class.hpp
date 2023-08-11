#include "headers.h"

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        auto prefix = nums, suffix = nums;
        for (int i = 1; i < n; ++i) {
            if (i % k != 0) {
                prefix[i] = std::max(prefix[i - 1], nums[i]);
            }
        }
        for (int i = n - 2; i >= 0; --i) {
            if (i % k != k - 1) {
                suffix[i] = std::max(suffix[i + 1], nums[i]);
            }
        }
        std::vector<int> ans(n - k + 1);
        for (int i = 0; i + k - 1 < n; ++i) {
            ans[i] = std::max(suffix[i], prefix[i + k - 1]);
        }
        return ans;
    }
};
