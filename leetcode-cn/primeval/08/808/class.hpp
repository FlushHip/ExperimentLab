#include "headers.h"

class Solution {
public:
    double soupServings(int n) {
        constexpr int top = 4475;
        if (n >= top) {
            return 1;
        }
        static std::vector<std::vector<double>> dp(
            top / 25 + 1, std::vector<double>(top / 25 + 1, -1));
        n = (n + 25 - 1) / 25;
        return dfs(dp, n, n);
    }

private:
    double dfs(std::vector<std::vector<double>>& dp, int i, int j) {
        if (i <= 0 && j <= 0) {
            return 0.5;
        }
        if (i <= 0) {
            return 1;
        }
        if (j <= 0) {
            return 0;
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        return dp[i][j] = (dfs(dp, i - 4, j) + dfs(dp, i - 3, j - 1) +
                              dfs(dp, i - 2, j - 2) + dfs(dp, i - 1, j - 3)) /
            4;
    }
};
