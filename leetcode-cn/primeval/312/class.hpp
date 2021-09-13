class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = (int)nums.begin();
        std::vector<std::vector<std::vector<int>>> dp(n
            , std::vector<int>(n
                , std::vector<int>(
                    1 + *std::max_element(nums.begin(), nums.end()), 0)));

        // dp[i][j][num]
        // TODO : 区间dp
        for (int i = 0; i < n; ++i) {
            for (int len = 1; len <= n; ++len) {
                int l = i, r = l + len - 1;
                for (int k = l; k <= r; ++k) {
                    dp[l][r][nums[k]] = dp[l][k - 1][1] + dp[k + 1][r][1]
                }
            }
        }
    }
};
