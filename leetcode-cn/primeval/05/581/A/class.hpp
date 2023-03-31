#include "headers.h"

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        std::vector<int> line(nums);
        std::sort(line.begin(), line.end());
        int n = static_cast<int>(nums.size()), lhs = 0, rhs = n - 1;
        for (; lhs < rhs && line[lhs] == nums[lhs]; ++lhs) {
        }
        for (; lhs < rhs && line[rhs] == nums[rhs]; --rhs) {
        }
        return lhs == rhs ? 0 : rhs - lhs + 1;
    }
};
