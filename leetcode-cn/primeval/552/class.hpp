class Solution {
public:
    Solution() {
        init();
    }
    int checkRecord(int n) {
        long long ans = 0;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                ans += dp[n][i][j];
            }
        }

        return static_cast<int>(ans % MOD);
    }

    void init() {
        std::memset(dp, 0, sizeof(long long) * TOP * 2 * 3);
        dp[1][0][1] = dp[1][0][2] = 1;
        dp[1][1][0] = 1;
        dp[0][0][2] = 1;
        for (int i = 2; i < TOP; ++i) {
            dp[i][0][1] = (dp[i - 1][0][2] + dp[i - 2][0][2]) % MOD;
            dp[i][0][2] = (dp[i - 1][0][1] + dp[i - 1][0][2]) % MOD;

            dp[i][1][0] = (dp[i - 1][0][1] + dp[i - 1][0][2]) % MOD;
            dp[i][1][1] = (dp[i - 1][1][0] + dp[i - 1][1][2]
                + dp[i - 2][1][0] + dp[i - 2][1][2]) % MOD;
            dp[i][1][2] = (dp[i - 1][1][0] + dp[i - 1][1][1]
                + dp[i - 1][1][2]) % MOD;
        }
    }
private:
    const static int TOP = 1e5 + 1;
    const static long long MOD = 1e9 + 7;
    long long dp[TOP][2][3];
};
