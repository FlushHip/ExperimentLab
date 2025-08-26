#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<long long> a(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            std::cin >> a[i];
        }
        dbg(n, a);
        std::vector<std::array<long long, 10>> dp(n + 1);
        for (int i = 1; i <= n; ++i) {
            for (int x = 0; x < 10; ++x) {
                long long no = dp[i - 1][x] + i;
                long long yes =
                    x <= i ? dp[i - 1][(x - 1 + 10) % 10] + x * a[i] + a[i] : 0;
                dp[i][x] = std::max(no, yes);
                dbg(i, x, no, yes, dp[i][x]);
            }
        }
        long long ans = *std::max_element(dp[n].begin(), dp[n].end());
        std::cout << ans << "\n";
    }
    return 0;
}
