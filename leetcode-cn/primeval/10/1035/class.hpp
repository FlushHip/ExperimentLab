#include "headers.h"

class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int n = static_cast<int>(nums1.size()),
            m = static_cast<int>(nums2.size());
        std::vector<std::vector<int>> dp(n, std::vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (nums1[i] == nums2[j]) {
                    dp[i][j] =
                        1 + (i - 1 < 0 || j - 1 < 0 ? 0 : dp[i - 1][j - 1]);
                } else {
                    dp[i][j] = std::max(i - 1 < 0 ? 0 : dp[i - 1][j],
                        j - 1 < 0 ? 0 : dp[i][j - 1]);
                }
            }
        }
        return dp[n - 1][m - 1];
    }
};
