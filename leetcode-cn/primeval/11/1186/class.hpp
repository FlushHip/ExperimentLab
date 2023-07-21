#include "headers.h"

class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        std::array<std::vector<int>, 2> dp;
        dp.fill(std::vector<int>(n));
        dp[0][0] = arr[0];
        dp[1][0] = 0;
        for (int i = 1; i < n; ++i) {
            dp[0][i] = std::max(arr[i], dp[0][i - 1] + arr[i]);
            dp[1][i] = std::max(dp[0][i - 1], dp[1][i - 1] + arr[i]);
        }
        return std::max(*std::max_element(dp[0].begin(), dp[0].end()),
            n == 1 ? std::numeric_limits<int>::min()
                   : *std::max_element(std::next(dp[1].begin()), dp[1].end()));
    }
};
