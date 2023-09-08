#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

#include <dbg.h>

int main() {
    constexpr long long mod = 1e9 + 7;
    for (int n{}; std::cin >> n;) {
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        dbg(a);
        auto total = std::accumulate(a.begin(), a.end(), 0);
        std::vector<std::vector<long long>> dp(
            n, std::vector<long long>(total + 1, -1));
        std::function<long long(int, int)> dfs = [&](int sum,
                                                     int index) -> long long {
            if (dp[index][sum] != -1) {
                return dp[index][sum];
            }
            int top = sum - index;
            if (index == 0) {
                return dp[index][sum] = sum != a[index];
            }
            auto ret = 0LL;
            for (int i = 1; i <= top; ++i) {
                if (a[index] != i) {
                    ret = (ret + dfs(sum - i, index - 1)) % mod;
                }
            }
            return dp[index][sum] = ret;
        };
        std::cout << dfs(total, n - 1) << std::endl;
        dbg(dp);
    }
    return 0;
}
