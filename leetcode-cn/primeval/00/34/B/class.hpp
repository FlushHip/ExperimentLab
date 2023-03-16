#include "headers.h"

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto [begin, end] = std::equal_range(nums.begin(), nums.end(), target);
        if (begin == nums.end() || *begin != target) {
            return {-1, -1};
        }
        return std::vector<int>{static_cast<int>(begin - nums.begin()),
            static_cast<int>(end - nums.begin() - 1)};
    }
};
