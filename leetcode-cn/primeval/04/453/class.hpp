#include "headers.h"

class Solution {
public:
    int minMoves(vector<int>& nums) {
        return std::accumulate(nums.begin(), nums.end(), 0,
            [min_value = *std::min_element(nums.begin(), nums.end())](
                int init, int value) { return init + value - min_value; });
    }
};
