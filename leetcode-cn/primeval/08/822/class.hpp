#include "headers.h"

class Solution {
public:
    int flipgame(vector<int>& fronts, vector<int>& backs) {
        std::unordered_set<int> ust;
        for (auto it_f = fronts.begin(), it_b = backs.begin();
             it_f != fronts.end(); ++it_f, ++it_b) {
            if (*it_f == *it_b) {
                ust.emplace(*it_f);
            }
        }
        int ans = std::numeric_limits<int>::max();
        for (int x : fronts) {
            if (!ust.count(x)) {
                ans = std::min(ans, x);
            }
        }
        for (int x : backs) {
            if (!ust.count(x)) {
                ans = std::min(ans, x);
            }
        }
        return ans == std::numeric_limits<int>::max() ? 0 : ans;
    }
};
