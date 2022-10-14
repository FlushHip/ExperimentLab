#include "headers.h"

// TLE
class Solution {
public:
    int distinctSubseqII(string s) {
        constexpr int mod = 1e9 + 7;
        int const n = static_cast<int>(s.size());
        std::vector<std::vector<std::vector<int>>> dp(
            n + 1, std::vector<std::vector<int>>(n, std::vector<int>(26, 0)));
        dp[1][0][s[0] - 'a'] = 1;
        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < 26; ++k) {
                dp[1][j][k] = dp[1][j - 1][k];
            }
            dp[1][j][s[j] - 'a'] = 1;
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = i - 1; j < n; ++j) {
                int sum = 0;
                for (int k = 0; k < 26; ++k) {
                    dp[i][j][k] = dp[i][j - 1][k];
                    sum = (sum + dp[i - 1][j - 1][k]) % mod;
                }
                int const t_k = s[j] - 'a';
                dp[i][j][t_k] = sum;
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans =
                (ans +
                    std::accumulate(dp[i][n - 1].begin(), dp[i][n - 1].end(), 0,
                        [mod](const int lhs, const int rhs) {
                            return (lhs + rhs) % mod;
                        })) %
                mod;
        }
        return ans;
    }
};
