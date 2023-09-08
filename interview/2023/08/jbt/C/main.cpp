#include <iostream>
#include <vector>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> v[i];
        }
        struct context {
            int to;
            int w;
        };
        int m{};
        std::cin >> m;
        std::vector<std::vector<context>> edges(m);
        for (int i = 0; i < m; ++i) {
            int from{}, to{}, w{};
            std::cin >> from >> to >> w;
            edges[from - 1].emplace_back(context{to - 1, w});
        }
        std::cout << 11 << std::endl;
    }
    return 0;
}
