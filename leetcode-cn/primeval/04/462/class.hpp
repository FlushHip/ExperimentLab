#include "headers.h"

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        return std::accumulate(nums.begin(), nums.end(), 0,
            [mid_value = *std::next(nums.begin(), nums.size() / 2)](int init,
                int value) { return init + std::abs(mid_value - value); });
    }
};
