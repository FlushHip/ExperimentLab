class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = (int)prices.size();
        std::vector<std::pair<int, int>> dp(n, { 0, 0 });
        dp[0].first = std::numeric_limits<int>::min();
        dp[0].second = -prices[0];

        for (int i = 1; i < n; ++i) {
            dp[i].first = std::max(dp[i - 1].first, dp[i - 1].second + prices[i]);
            dp[i].second = std::max(-prices[i], std::max(dp[i - 1].second, i - 2 > 0
                ? dp[i - 2].first - prices[i]
                : std::numeric_limits<int>::min()));
        }

        return std::max(0, dp[n - 1].first);
    }
};
