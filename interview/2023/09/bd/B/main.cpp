#include <iostream>
#include <numeric>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}, m{}, k{}, a{}; std::cin >> n >> m >> k >> a;) {
        std::vector<int> line(n + 2, 0);
        std::vector<std::pair<int, int>> prs(m);
        for (int i = 0; i < m; ++i) {
            std::cin >> prs[i].first;
        }
        for (int i = 0; i < m; ++i) {
            std::cin >> prs[i].second;
        }
        for (auto&& [lhs, rhs] : prs) {
            ++line[lhs];
            --line[rhs + 1];
        }
        std::partial_sum(line.begin(), line.end(), line.begin());
        dbg(line);
        int ans = 0;
        for (int lhs = 1, rhs = 1; lhs <= n; lhs = rhs) {
            for (; lhs <= n && line[lhs] >= a; ++lhs) {
            }
            for (rhs = lhs; rhs <= n && line[rhs] < a; ++rhs) {
            }
            int cnt = rhs - lhs;
            ans += cnt >= k ? cnt - k + 1 : 0;
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
