#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    constexpr long long mod = 1e9 + 7;
    for (int m{}; std::cin >> m;) {
        std::vector<std::pair<int, int>> lines(m);
        for (int i = 0; i < m; ++i) {
            std::cin >> lines[i].first >> lines[i].second;
        }
        std::sort(
            lines.begin(), lines.end(), [](const auto& lhs, const auto& rhs) {
                return lhs.second < rhs.second;
            });
        std::vector<long long> dp(m, 0);
        dp[0] = 2;
        for (int i = 1; i < m; ++i) {
            dp[i] = dp[i - 1];
            auto it = std::lower_bound(lines.begin(), lines.end(),
                lines[i].first, [](const auto& lhs, const auto& rhs) {
                    return lhs.second < rhs;
                });
            if (it != lines.begin()) {
                dp[i] = (dp[i] + dp[std::prev(it) - lines.begin()]) % mod;
            } else {
                dp[i] = (dp[i] + 1) % mod;
            }
        }
        std::cout << dp[m - 1] << std::endl;
    }
    return 0;
}
