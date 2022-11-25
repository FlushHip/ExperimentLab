#include "headers.h"

class Solution {
public:
    int superEggDrop(int k, int n) {
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, -1));
        return dfs(n, k, dp);
    }

private:
    int dfs(int n, int k, std::vector<std::vector<int>>& dp) {
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        if (k == 1) {
            return n;
        }
        if (dp[n][k] != -1) {
            return dp[n][k];
        }
        int res = std::numeric_limits<int>::max();
        int lhs = 0, rhs = n;
        while (lhs < rhs) {
            int mid = (lhs + rhs + 1) / 2;
            if (dfs(n - mid, k, dp) < dfs(mid - 1, k - 1, dp)) {
                rhs = mid - 1;
            } else {
                lhs = mid;
            }
        }
        return dp[n][k] = std::min(rhs == 0 ? res
                                            : 1 +
                           std::max(
                               dfs(n - rhs, k, dp), dfs(rhs - 1, k - 1, dp)),
                   rhs + 1 > n ? res
                               : 1 +
                           std::max(dfs(n - (rhs + 1), k, dp),
                               dfs((rhs + 1) - 1, k - 1, dp)));
    }
};
