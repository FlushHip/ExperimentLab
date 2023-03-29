#include "headers.h"

class Solution {
public:
    int countSubstrings(string s) {
        int n = static_cast<int>(s.size());
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;
        }
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
                dp[i][i + len - 1] = s[i] == s[i + len - 1] &&
                    (!(i + 1 <= i + len - 2) || dp[i + 1][i + len - 2]);
            }
        }
        int ans = 0;
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
                ans += dp[i][i + len - 1];
            }
        }
        return ans;
    }
};
