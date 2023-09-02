#include <iostream>
#include <limits>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<int> line(n + 1, 0);
        std::vector<int> pre(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            std::cin >> line[i];
            pre[i] = pre[i - 1] + line[i];
        }
        dbg(line, pre);
        std::vector<std::vector<int>> dp(
            n + 1, std::vector(n + 1, std::numeric_limits<int>::min()));
        for (int i = 1; i <= n; ++i) {
            dp[i][i] = line[i];
        }
        for (int L = 2; L <= n; ++L) {
            for (int i = 1; i + L - 1 <= n; ++i) {
                int j = i + L - 1;
                dp[i][j] = pre[j] - pre[i - 1];
                for (int lhs = i; lhs < j; ++lhs) {
                    dp[i][j] = std::max(dp[i][j],
                        pre[lhs] - pre[i - 1] + pre[j] - pre[lhs] -
                            dp[lhs + 1][j]);
                }
                for (int rhs = j; rhs > i; --rhs) {
                    dp[i][j] = std::max(dp[i][j],
                        pre[j] - pre[rhs - 1] + pre[rhs - 1] - pre[i - 1] -
                            dp[i][rhs - 1]);
                }
                dbg(i, j, dp[i][j]);
            }
        }
        std::cout << dp[1][n] - (pre[n] - dp[1][n]) << std::endl;
    }
    return 0;
}
