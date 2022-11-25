#include "headers.h"

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        Dp dp(n + 2, std::vector<int>(n + 2, -1));
        return dfs(0, n + 1, dp, nums);
    }

private:
    using Dp = std::vector<std::vector<int>>;

    int dfs(int lhs, int rhs, Dp& dp, const std::vector<int>& nums) {
        if (rhs - lhs == 1) {
            return 0;
        }
        if (dp[lhs][rhs] != -1) {
            return dp[lhs][rhs];
        }

        int res = 0;
        for (int i = lhs + 1; i < rhs; ++i) {
            res = std::max(res,
                dfs(lhs, i, dp, nums) + dfs(i, rhs, dp, nums) +
                    nums[lhs] * nums[i] * nums[rhs]);
        }
        return dp[lhs][rhs] = res;
    }
};
