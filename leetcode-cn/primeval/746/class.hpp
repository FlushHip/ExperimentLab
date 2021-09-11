class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = (int)cost.size();
        std::vector<int> dp(n + 1);
        for (int i = 0; i < n + 1; ++i) {
            dp[i] = std::min(i - 1 < 0 ? 0 : dp[i -  1] + cost[i - 1]
                , i - 2 < 0 ? 0 : dp[i - 2] + cost[i - 2]);
        }
        return dp[n];
    }
};
