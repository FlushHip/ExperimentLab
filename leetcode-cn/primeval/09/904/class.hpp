#include "headers.h"

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        std::unordered_map<int, int> mp;
        int ans = 0;
        for (int lhs = 0, rhs = 0; rhs < static_cast<int>(fruits.size());) {
            if (mp.size() > 2) {
                --mp[fruits[lhs]];
                if (!mp[fruits[lhs]]) {
                    mp.erase(fruits[lhs]);
                }
                ++lhs;
            } else {
                ++mp[fruits[rhs]];
                if (mp.size() <= 2) {
                    ans = std::max(ans, rhs - lhs + 1);
                }
                ++rhs;
            }
        }
        return ans;
    }
};
