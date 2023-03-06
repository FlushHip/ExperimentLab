#include "headers.h"

class Solution {
public:
    vector<int> numberOfPairs(vector<int>& nums) {
        std::unordered_map<int, int> mp;
        for (int num : nums) {
            ++mp[num];
        }

        int ans1 = 0, ans2 = 0;
        for (auto [_, value] : mp) {
            ans1 += value / 2;
            ans2 += value % 2;
        }
        return {ans1, ans2};
    }
};
