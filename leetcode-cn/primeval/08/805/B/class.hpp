#include "headers.h"

class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        constexpr int n_mvalue = 30, num_mvalue = 10000;
        // 这两个static是优化的关键
        static int dp[n_mvalue][n_mvalue * num_mvalue + 1][n_mvalue + 1];
        static int opt_index = 0;

        int n = nums.size(), top = std::accumulate(nums.begin(), nums.end(), 0);
        ++opt_index;
        for (int k = 1; k <= n / 2; ++k) {
            if (top * k % n == 0 &&
                dfs(n - 1, top * k / n, k, opt_index, nums, dp)) {
                return true;
            }
        }
        return false;
    }

private:
    template <class T>
    bool dfs(int i,
        int j,
        int k,
        int opt_index,
        const std::vector<int>& nums,
        T& dp) {
        if (i < 0) {
            return j == 0 && k == 0;
        }
        if (dp[i][j][k] >= opt_index * 2) {
            return dp[i][j][k] - opt_index * 2;
        }
        return (dp[i][j][k] = (dfs(i - 1, j, k, opt_index, nums, dp) ||
                                  (j >= nums[i] && k > 0
                                          ? dfs(i - 1, j - nums[i], k - 1,
                                                opt_index, nums, dp)
                                          : false))
                       ? 2 * opt_index + 1
                       : 2 * opt_index) -
            2 * opt_index;
    }
};
