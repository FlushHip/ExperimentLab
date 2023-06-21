#include "headers.h"

class Solution {
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        int n = static_cast<int>(s.size());
        std::vector<std::array<int, 26>> sums(n);
        sums[0][s[0] - 'a'] = 1;
        for (int i = 1; i < n; ++i) {
            sums[i] = sums[i - 1];
            ++sums[i][s[i] - 'a'];
        }
        std::vector<bool> ans;
        for (const auto& query : queries) {
            int lhs = query[0], rhs = query[1], k = query[2];
            int odd = 0;
            for (int i = 0; i < 26; ++i) {
                if ((sums[rhs][i] - (lhs == 0 ? 0 : sums[lhs - 1][i])) % 2) {
                    ++odd;
                }
            }
            ans.emplace_back(odd / 2 <= k);
        }
        return ans;
    }
};
