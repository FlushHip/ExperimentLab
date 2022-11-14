#include "headers.h"

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

        std::vector<std::vector<std::unordered_set<int>>> dp(
            2, std::vector<std::unordered_set<int>>(n / 2 + 1));
        dp[0][0].emplace(0);
        dp[0][1].emplace(nums[0]);
        for (int i = 1; i < n; ++i) {
            dp[i % 2] = dp[(i - 1) % 2];
            for (int k = 1; k <= n / 2; ++k) {
                for (int x : dp[(i - 1) % 2][k - 1]) {
                    int cur = x + nums[i];
                    if (cur * n == top * k) {
                        return true;
                    }
                    dp[i % 2][k].emplace(cur);
                }
            }
        }
        return false;
    }
};
