#include "headers.h"

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::vector<int> min_values(n), max_values(n);
        min_values[n - 1] = nums[n - 1];
        max_values[0] = nums[0];
        for (int i = n - 2; i >= 0; --i) {
            min_values[i] = std::min(nums[i], min_values[i + 1]);
        }
        for (int i = 1; i < n; ++i) {
            max_values[i] = std::max(nums[i], max_values[i - 1]);
        }
        int lhs = 0, rhs = n - 1;
        for (; lhs < rhs && nums[lhs] <= min_values[lhs + 1]; ++lhs) {
        }
        for (; lhs < rhs && nums[rhs] >= max_values[rhs - 1]; --rhs) {
        }
        return lhs == rhs ? 0 : rhs - lhs + 1;
    }
};
