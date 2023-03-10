#include "headers.h"

class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        const int n = static_cast<int>(nums1.size());
        std::vector<std::array<int, 2>> dp(n);
        dp[0][0] = 0, dp[0][1] = 1;

        for (int i = 1; i < n; ++i) {
            dp[i][0] = nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1]
                ? (nums2[i] > nums1[i - 1] && nums1[i] > nums2[i - 1]
                          ? std::min(dp[i - 1][0], dp[i - 1][1])
                          : dp[i - 1][0])
                : dp[i - 1][1];
            dp[i][1] = 1 +
                (nums2[i] > nums1[i - 1] && nums1[i] > nums2[i - 1]
                        ? (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1]
                                  ? std::min(dp[i - 1][0], dp[i - 1][1])
                                  : dp[i - 1][0])
                        : dp[i - 1][1]);
        }
        return std::min(dp[n - 1][0], dp[n - 1][1]);
    }
};
