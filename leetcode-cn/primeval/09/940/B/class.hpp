#include "headers.h"

class Solution {
public:
    int distinctSubseqII(string s) {
        constexpr int mod = 1e9 + 7;
        int const n = static_cast<int>(s.size());
        std::vector<std::array<int, 26>> dp(n, {0});
        dp[0][s[0] - 'a'] = 1;
        for (int i = 1; i < n; ++i) {
            int sum = 1;
            for (int k = 0; k < 26; ++k) {
                dp[i][k] = dp[i - 1][k];
                sum = (sum + dp[i - 1][k]) % mod;
            }
            dp[i][s[i] - 'a'] = sum;
        }
        int ans = 0;
        for (int i = 0; i < 26; ++i) {
            ans = (ans + dp[n - 1][i]) % mod;
        }
        return ans;
    }
};
