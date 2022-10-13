class Solution {
public:
    int rob(vector<int>& nums) {
        if (!nums.size()) {
            return 0;
        }
        if (1 == nums.size()) {
            return nums.front();
        }
        int last = nums.back();
        nums.pop_back();
        int ans1 = rob_aux(nums);
        nums.push_back(last);
        nums.erase(nums.begin());
        int ans2 = rob_aux(nums);
        return std::max(ans1, ans2);
    }
    int rob_aux(const std::vector<int>& nums) {
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
