#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        std::vector<std::vector<int>> edges(n);
        for (int i = 0; i < n - 1; ++i) {
            int u{}, v{};
            std::cin >> u >> v;
            edges[u - 1].emplace_back(v - 1);
            edges[v - 1].emplace_back(u - 1);
        }

        std::vector<std::array<int, 2>> dp(n, {-1, -1});
        std::function<int(int, int, int)> dfs = [&](int root, int self,
                                                    int pre) -> int {
            if (dp[root][self] != -1) {
                return dp[root][self];
            }

            if (self == 0) {
                int ans_0 = 0;
                for (auto e : edges[root]) {
                    if (e != pre) {
                        ans_0 += std::max(dfs(e, 0, root), dfs(e, 1, root));
                    }
                }
                dbg(root, self, ans_0);
                return dp[root][self] = ans_0;
            }

            int ans_1 = 0;
            for (auto e : edges[root]) {
                if (auto x = static_cast<long long>(std::sqrt(a[root] * a[e]));
                    e != pre && x * x == a[root] * a[e]) {
                    // dbg(next_sum, last_sum, dfs(e, 0, root));
                    ans_1 = std::max(ans_1,
                        2 + dfs(root, 0, pre) -
                            std::max(dfs(e, 0, root), dfs(e, 1, root)) +
                            dfs(e, 0, root));
                }
            }
            return dp[root][self] = ans_1;
        };
        std::cout << std::max(dfs(0, 0, -1), dfs(0, 1, -1)) << std::endl;
    }
    return 0;
}
