#include "headers.h"

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int max_value = *std::max_element(candies.begin(), candies.end());
        std::vector<bool> ans(candies.size());
        for (auto i = 0U; i < candies.size(); ++i) {
            ans[i] = candies[i] + extraCandies >= max_value;
        }
        return ans;
    }
};
