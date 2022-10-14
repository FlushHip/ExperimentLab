class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = (int)nums.size();
        std::vector<bool> dp(n, false);
        dp[0] = true;
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (i - j <= nums[j] && dp[j]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp.back();
    }
};
