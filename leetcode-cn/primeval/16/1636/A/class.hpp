#include "headers.h"

class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        std::map<int, int> mp;
        for (auto num : nums) {
            ++mp[num];
        }
        std::vector<std::pair<int, int>> vp;
        for (const auto& [value, count] : mp) {
            vp.emplace_back(count, value);
        }
        std::sort(vp.begin(), vp.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.first == rhs.first ? lhs.second > rhs.second
                                          : lhs.first < rhs.first;
        });
        std::vector<int> ans(nums.size());
        auto index = 0U;
        for (const auto& [count, value] : vp) {
            std::fill_n(ans.begin() + index, count, value);
            index += count;
        }
        return ans;
    }
};
