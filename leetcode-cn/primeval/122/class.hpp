class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = (int)prices.size();
        std::vector<std::pair<int, int>> dp(n, { 0, 0 });
        dp[0].first = -prices[0];
        dp[0].second = 0;

        for (int i = 1; i < n; ++i) {
            dp[i].first = std::max(dp[i - 1].first, dp[i - 1].second - prices[i]);
            dp[i].second = std::max(dp[i - 1].second, dp[i - 1].first + prices[i]);
        }

        return dp[n - 1].second;
    }
};
