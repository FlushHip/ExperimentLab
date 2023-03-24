#include "headers.h"

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        std::unordered_map<int, int> ust{{0, 1}};
        for (int num : nums) {
            auto pre_ust = std::move(ust);
            for (auto [sum, cnt] : pre_ust) {
                ust[sum + num] += cnt;
                ust[sum - num] += cnt;
            }
        }
        return ust[target];
    }
};
