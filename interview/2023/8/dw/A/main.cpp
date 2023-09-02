#include <iostream>
#include <limits>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}, m{}; std::cin >> n >> m;) {
        std::vector<int> line(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> line[i];
        }
        dbg(line);
        std::vector<int> dp(m + 1, std::numeric_limits<int>::max());
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = m; j >= line[i]; --j) {
                if (dp[j - line[i]] != std::numeric_limits<int>::max()) {
                    dp[j] = std::min(dp[j], 1 + dp[j - line[i]]);
                }
            }
        }
        if (dp[m] == std::numeric_limits<int>::max()) {
            std::cout << "No solution";
        } else {
            std::cout << dp[m];
        }
        std::cout << std::endl;
    }
    return 0;
}
