#include "headers.h"

class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> sums(n, 0);
        std::partial_sum(nums.begin(), nums.end(), sums.begin());
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        int value = dfs(0, n - 1, nums, sums, dp);
        return value >= sums[n - 1] - value;
    }

private:
    int dfs(int l,
        int r,
        const std::vector<int>& nums,
        const std::vector<int>& sums,
        std::vector<std::vector<int>>& dp) {
        if (l == r) {
            return dp[l][r] = nums[l];
        }
        if (dp[l][r]) {
            return dp[l][r];
        }
        return dp[l][r] = std::max(nums[l] +
                       (sums[r] - sums[l] - dfs(l + 1, r, nums, sums, dp)),
                   nums[r] +
                       (sums[r - 1] - (l - 1 < 0 ? 0 : sums[l - 1]) -
                           dfs(l, r - 1, nums, sums, dp)));
    }
};
