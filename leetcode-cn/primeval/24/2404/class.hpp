#include "headers.h"

class Solution {
public:
    int mostFrequentEven(vector<int>& nums) {
        std::map<int, int> mp;
        for (int i : nums) {
            if (i % 2 == 0) {
                ++mp[i];
            }
        }
        return mp.empty() ? -1
                          : std::max_element(mp.begin(), mp.end(),
                                [](const auto& largest, const auto& pr) {
                                    return largest.second < pr.second;
                                })
                                ->first;
    }
};
