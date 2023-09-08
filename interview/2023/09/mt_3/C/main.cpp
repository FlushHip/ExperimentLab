#include <iostream>
#include <vector>

int main() {
    for (int n{}, m{}; std::cin >> n >> m;) {
        std::vector<long long> ans(m, 0);
        for (int L = 0; L < n; ++L) {
            int k{}, c{}, p{};
            std::cin >> k >> c;
            auto ceil = (0LL + c + k - 1) / k;
            for (int i = 0; i < k - 1; ++i) {
                std::cin >> p;
                ans[--p] += ceil;
            }
        }
        for (int i = 0; i < m; ++i) {
            std::cout << ans[i] << " \n"[i + 1 == m];
        }
    }
    return 0;
}
