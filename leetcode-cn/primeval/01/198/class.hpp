class Solution {
public:
    int rob(vector<int>& nums) {
        const int n = nums.size();
        if (!n) {
            return 0;
        }
        if (1 == n) {
            return nums[0];
        }

        std::vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = std::max(dp[0], nums[1]);
        for (int i = 2; i < n; ++i) {
            dp[i] = std::max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[n - 1];
    }
};
