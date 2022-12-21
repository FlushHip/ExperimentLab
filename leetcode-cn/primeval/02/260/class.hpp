#include "headers.h"

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int x = std::accumulate(nums.begin(), nums.end(), 0,
                [](int init, int num) { return init ^ num; }),
            a = 0, b = 0;
        std::for_each(nums.begin(), nums.end(),
            [&a, &b, mask = x - (x & (x - 1ll))](
                int num) { (void)((num & mask) ? a ^= num : b ^= num); });
        return {a, b};
    }
};
