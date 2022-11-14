#include "headers.h"

// TLE, 递推的dp超时
class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int n = nums.size(), top = std::accumulate(nums.begin(), nums.end(), 0);
        int f = false;
        for (int k = 1; k < n; ++k) {
            if (top * k % n == 0) {
                f = true;
                break;
            }
        }
        if (!f) {
            return false;
        }
        std::vector<std::vector<std::vector<bool>>> dp(2,
            std::vector<std::vector<bool>>(
                top + 1, std::vector<bool>(n + 1, false)));
        dp[0][nums[0]][1] = true;
        for (int i = 0; i < 2; ++i) {
            dp[i][0][0] = true;
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= top; ++j) {
                for (int k = 1; k <= std::max(i + 1, n / 2); ++k) {
                    dp[i % 2][j][k] =
                        (j >= nums[i] ? dp[(i - 1) % 2][j - nums[i]][k - 1]
                                      : false) ||
                        dp[(i - 1) % 2][j][k];
                }
            }
            for (int k = 1; k < n; ++k) {
                if (top * k % n == 0 && dp[i % 2][top * k / n][k]) {
                    return true;
                }
            }
        }
        for (int k = 1; k < n; ++k) {
            if (top * k % n == 0 && dp[(n - 1) % 2][top * k / n][k]) {
                return true;
            }
        }
        return false;
    }
};
