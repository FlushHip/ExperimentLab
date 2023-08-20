#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

int main() {
    for (int n{}, m{}, k{}; std::cin >> n >> m >> k;) {
        std::vector<long long> a(n), h(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> h[i];
        }
        struct node_t {
            int idx;
            long long w;
        };
        std::unordered_map<int, std::vector<node_t>> ump;
        for (int i = 0; i < m; ++i) {
            int u{}, v{}, w{};
            std::cin >> u >> v >> w;
            ump[u - 1].push_back(node_t{v - 1, w});
            ump[v - 1].push_back(node_t{u - 1, w});
        }
        long long ans = std::numeric_limits<long long>::min();
        // 1
        for (int i = 0; i < n; ++i) {
            if (h[i] <= k) {
                ans = std::max(ans, h[i]);
            }
        }
        // 2
        for (auto& [u, edges] : ump) {
            for (auto it = edges.begin(); it != edges.end(); ++it) {
                if (u > it->idx && h[u] + h[it->idx] + it->w <= k) {
                    ans = std::max(ans, a[u] + a[it->idx]);
                }
            }
        }
        // 3
        for (auto& [u, edges] : ump) {
            for (auto it1 = edges.begin(); it1 != edges.end(); ++it1) {
                for (auto it2 = edges.begin(); it2 != edges.end(); ++it2) {
                    if (it1->idx < it2->idx &&
                        h[u] + h[it1->idx] + h[it2->idx] + it1->w + it2->w <=
                            k) {
                        ans = std::max(ans, a[u] + a[it1->idx] + a[it2->idx]);
                    }
                }
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
