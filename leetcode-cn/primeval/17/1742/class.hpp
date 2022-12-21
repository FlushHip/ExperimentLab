#include "headers.h"

class Solution {
public:
    int countBalls(int lowLimit, int highLimit) {
        std::unordered_map<int, int> mp;
        for (int i = lowLimit; i <= highLimit; ++i) {
            int ret = 0;
            for (int ii = i; ii; ii /= 10) {
                ret += ii % 10;
            }
            ++mp[ret];
        }
        int ans = 0;
        for (auto [_, cnt] : mp) {
            ans = std::max(cnt, ans);
        }
        return ans;
    }
};
