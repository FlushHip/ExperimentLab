#include "headers.h"

class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        std::vector<int> diff;
        auto it_diff = std::back_inserter(diff);
        for (auto it1 = reward1.begin(), it2 = reward2.begin();
             it1 != reward1.end() && it2 != reward2.end(); ++it1, ++it2) {
            *it_diff++ = *it1 - *it2;
        }
        std::sort(diff.begin(), diff.end(), std::greater<>{});
        return std::accumulate(reward2.begin(), reward2.end(), 0) +
            std::accumulate(diff.begin(), diff.begin() + k, 0);
    }
};
