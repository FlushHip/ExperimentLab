class Solution {
public:
    vector<int> countBits(int n) {
        std::vector<int> dp(n + 1, 0);
        for (int i = 1, t = 0; i <= n; ++i) {
            if (!(i & (i - 1))) {
                t = i;
            }
            dp[i] = dp[i - t] + 1;
        }
        return dp;
    }
};
