#include "headers.h"

class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = static_cast<int>(arr.size());
        std::vector<int> dp(n, 0);
        for (int i = 0; i < n; ++i) {
            int max_value = 0;
            for (int L = 1; L <= k && i + 1 - L >= 0; ++L) {
                max_value = std::max(max_value, arr[i + 1 - L]);
                dp[i] = std::max(
                    dp[i], (i - L < 0 ? 0 : dp[i - L]) + max_value * L);
            }
        }
        return dp[n - 1];
    }
};
