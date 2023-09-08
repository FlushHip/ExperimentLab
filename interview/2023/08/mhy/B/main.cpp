#include <cassert>
#include <iostream>
#include <vector>

struct node_t {
    std::vector<int> clds;
};

long long dfs(const std::vector<node_t>& tbs, int root, int pre, int k) {
    if (k == 0) {
        return 1;
    }
    long long ret = 1;
    if (tbs[root].clds.size() == 1) {
        return ret + k;
    }
    for (auto cld : tbs[root].clds) {
        if (cld != pre) {
            ret += dfs(tbs, cld, root, k - 1);
        }
    }
    return ret;
}

int main() {
    for (int n{}, k{}; std::cin >> n >> k;) {
        std::vector<node_t> tbs(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u{}, v{};
            std::cin >> u >> v;
            tbs[u].clds.push_back(v);
            tbs[v].clds.push_back(u);
        }
        std::cout << dfs(tbs, 1, 0, k) << std::endl;
    }
    return 0;
}
