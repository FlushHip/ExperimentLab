#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    for (int t{}; std::cin >> t;) {
        while (t--) {
            int n{}, k{};
            std::cin >> n >> k;
            std::vector<int> a(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> a[i];
            }
            for (int i = 0; i < k; ++i) {
                int u{}, v{};
                std::cin >> u >> v;
                ++a[--u], --a[--v];
            }
            std::cout << (std::is_sorted(a.begin(), a.end()) ? "Yes" : "No")
                      << std::endl;
        }
    }
    return 0;
}
