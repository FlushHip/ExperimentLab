#include "headers.h"

class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int n = nums.size(), top = std::accumulate(nums.begin(), nums.end(), 0);
        std::array<std::vector<int>, 2> dp{std::vector<int>(top + 1, 0)};
        dp[0][0] = 1;
        dp[0][nums[0]] |= 1 << 1;
        for (int i = 1; i < n; ++i) {
            dp[i % 2] = dp[(i - 1) % 2];
            for (int j = nums[i]; j <= top; ++j) {
                dp[i % 2][j] |= dp[(i - 1) % 2][j - nums[i]] << 1;
            }

            for (int k = 1; k <= n / 2; ++k) {
                if (top * k % n == 0 && (dp[i % 2][top * k / n] & (1 << k))) {
                    return true;
                }
            }
        }
        return false;
    }
};
