#include "headers.h"

class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::unordered_map<int, int> ump;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ++ump[nums[i] * nums[j]];
            }
        }
        int ret = 0;
        for (const auto& [_, cnt] : ump) {
            ret += 8 * cnt * (cnt - 1) / 2;
        }
        return ret;
    }
};
