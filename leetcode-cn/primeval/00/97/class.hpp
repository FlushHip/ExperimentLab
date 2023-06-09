#include "headers.h"

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = static_cast<int>(s1.size()), n2 = static_cast<int>(s2.size()),
            n3 = static_cast<int>(s3.size());
        if (n1 + n2 != n3) {
            return false;
        }
        std::vector<std::vector<bool>> dp(
            n1 + 1, std::vector<bool>(n2 + 1, false));
        dp[0][0] = true;
        for (int i = 0; i < n1; ++i) {
            dp[i + 1][0] = dp[i][0] && s3[i] == s1[i];
        }
        for (int j = 0; j < n2; ++j) {
            dp[0][j + 1] = dp[0][j] && s3[j] == s2[j];
        }
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < n2; ++j) {
                if (s3[i + j + 1] == s1[i]) {
                    dp[i + 1][j + 1] = dp[i + 1][j + 1] || dp[i][j + 1];
                }
                if (s3[i + j + 1] == s2[j]) {
                    dp[i + 1][j + 1] = dp[i + 1][j + 1] || dp[i + 1][j];
                }
            }
        }
        return dp[n1][n2];
    }
};
