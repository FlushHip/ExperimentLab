#include "headers.h"

class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        std::map<int, int> mp;
        for (auto num : nums) {
            ++mp[num];
        }
        std::sort(
            nums.begin(), nums.end(), [&mp](const auto& lhs, const auto& rhs) {
                return mp[lhs] == mp[rhs] ? lhs > rhs : mp[lhs] < mp[rhs];
            });
        return nums;
    }
};
