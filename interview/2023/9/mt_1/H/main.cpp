#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}, m{}; std::cin >> n >> m;) {
        std::vector<std::vector<int>> matrix(n + 1, std::vector<int>(m + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                std::cin >> matrix[i][j];
            }
        }
        dbg(matrix);
        auto sum = std::accumulate(
            matrix.begin(), matrix.end(), 0LL, [](auto init, const auto& line) {
                return init + std::accumulate(line.begin(), line.end(), 0LL);
            });
        dbg(sum);
        long long ans = sum, t_sum = 0;
        for (int i = 0; i <= n; ++i) {
            t_sum += std::accumulate(matrix[i].begin(), matrix[i].end(), 0LL);
            ans = std::min(ans, std::abs(sum - t_sum - t_sum));
        }
        t_sum = 0;
        for (int j = 0; j <= m; ++j) {
            t_sum += std::accumulate(matrix.begin(), matrix.end(), 0LL,
                [j](auto init, const auto& line) { return init + line[j]; });
            ans = std::min(ans, std::abs(sum - t_sum - t_sum));
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
