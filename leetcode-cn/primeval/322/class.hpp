// TAG : 完全背包
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        std::vector<int> dp(amount + 1, -1);
        dp[0] = 0;
        for (auto it = coins.begin(); it != coins.end(); ++it) {
            for (int i = *it; i <= amount; ++i) {
                if (dp[i - *it] + 1) {
                    if (dp[i] + 1) {
                        dp[i] = std::min(dp[i], dp[i - *it] + 1);
                    } else {
                        dp[i] = dp[i - *it] + 1;
                    }
                }
            }
        }
        return dp[amount];
    }
};
