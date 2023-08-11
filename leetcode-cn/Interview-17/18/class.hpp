#include "headers.h"

class Solution {
public:
    vector<int> shortestSeq(vector<int>& big, vector<int>& small) {
        int m = static_cast<int>(small.size());
        std::unordered_set<int> ust;
        for (int e : small) {
            ust.emplace(e);
        }
        std::unordered_map<int, int> ump;
        int n = static_cast<int>(big.size());

        int min_value = n + 1;
        std::vector<int> ans;

        for (int rhs = 0, lhs = 0; rhs < n; ++rhs) {
            if (ust.contains(big[rhs])) {
                ++ump[big[rhs]];
                for (; lhs <= rhs && ump.size() == m; ++lhs) {
                    if (min_value > rhs - lhs + 1) {
                        min_value = rhs - lhs + 1;
                        ans = {lhs, rhs};
                    }
                    if (ust.contains(big[lhs]) && --ump[big[lhs]] == 0) {
                        ump.erase(big[lhs]);
                    }
                }
            }
        }
        return ans;
    }
};