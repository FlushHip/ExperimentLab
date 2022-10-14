#include "headers.h"

class Solution {
public:
    int numDistinct(string s, string t) {
        int n = static_cast<int>(s.size()), m = static_cast<int>(t.size());
        int lhs = 0, rhs = 0;
        for (; lhs < m && rhs < n;) {
            if (t[lhs] == s[rhs]) {
                ++lhs;
                ++rhs;
            } else {
                ++rhs;
            }
        }
        if (lhs != m) {
            return 0;
        }
        std::vector<std::vector<long long>> dp(
            m + 1, std::vector<long long>(n + 1, 0));
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = 1;
        }
        for (int i = 0; i < m; ++i) {
            for (int j = i; j < n; ++j) {
                if (t[i] != s[j]) {
                    dp[i + 1][j + 1] = dp[i + 1][j];
                } else {
                    dp[i + 1][j + 1] = dp[i][j] + dp[i + 1][j];
                    if (dp[i + 1][j + 1] > std::numeric_limits<int>::max()) {
                        dp[i + 1][j + 1] = 0;
                    }
                }
            }
        }
        return dp[m][n];
    }
};
