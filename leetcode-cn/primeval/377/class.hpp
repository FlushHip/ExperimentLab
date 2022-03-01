class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        std::vector<unsigned int> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; ++i) {
            for (int j = 0; j < (int)nums.size(); ++j) {
                dp[i] += i - nums[j] >= 0 ? dp[i - nums[j]] : 0;
            }
        }
        return dp[target];
    }
};
