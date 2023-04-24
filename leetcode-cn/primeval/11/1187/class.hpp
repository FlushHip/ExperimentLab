#include "headers.h"

class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        std::sort(arr2.begin(), arr2.end());
        arr2.erase(std::unique(arr2.begin(), arr2.end()), arr2.end());
        int n = static_cast<int>(arr1.size()),
            m = static_cast<int>(arr2.size());
        std::vector<std::vector<unsigned int>> dp(
            n, std::vector<unsigned int>(m + 1, -1));
        for (int i = 0; i < m; ++i) {
            dp[0][i] = 1;
        }
        dp[0][m] = 0;

        for (int i = 1; i < n; ++i) {
            // 0 0
            if (arr1[i - 1] < arr1[i]) {
                dp[i][m] = dp[i - 1][m];
            }
            // 1 0
            for (int j = 0; j < m && arr2[j] < arr1[i]; ++j) {
                if (dp[i - 1][j] != -1) {
                    dp[i][m] = std::min(dp[i][m], dp[i - 1][j]);
                }
            }
            // 0 1
            if (auto it =
                    std::lower_bound(arr2.begin(), arr2.end(), arr1[i - 1] + 1);
                it != arr2.end() && dp[i - 1][m] != -1) {
                for (int k = static_cast<int>(it - arr2.begin()); k < m; ++k) {
                    dp[i][k] = dp[i - 1][m] + 1;
                }
            }
            // 1 1
            for (int k = 1; k < m; ++k) {
                if (dp[i - 1][k - 1] != -1) {
                    dp[i][k] = std::min(dp[i][k], dp[i - 1][k - 1] + 1);
                }
            }
        }
        return *std::min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};
