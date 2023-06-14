#include "headers.h"

class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells,
        vector<int>& potions,
        long long success) {
        std::sort(potions.begin(), potions.end());
        int n = static_cast<int>(spells.size()),
            m = static_cast<int>(potions.size());
        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            int lhs = 0, rhs = m;
            while (lhs < rhs) {
                int mid = (lhs + rhs) / 2;
                if (1LL * potions[mid] * spells[i] < success) {
                    lhs = mid + 1;
                } else {
                    rhs = mid;
                }
            }
            ans[i] = m - lhs;
        }
        return ans;
    }
};
