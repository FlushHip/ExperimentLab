#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include <dbg.h>

struct ctx_t {
    int u, v;
    int value;
    friend std::ostream& operator<<(std::ostream& os, const ctx_t& ctx) {
        os << "{" << ctx.u << ", " << ctx.v << ", " << ctx.value << "}";
        return os;
    }
};

int main() {
    for (int n{}, m{}; std::cin >> n >> m;) {
        std::vector<ctx_t> lines(m);
        for (int i = 0; i < m; ++i) {
            std::cin >> lines[i].u >> lines[i].v >> lines[i].value;
        }
        dbg(lines);
        std::sort(lines.begin(), lines.end(),
            [](auto&& lhs, auto&& rhs) { return lhs.value > rhs.value; });
        dbg(lines);
        std::vector<int> pre(n + 1, 0);
        std::function<int(int)> find = [&](int x) {
            return pre[x] != 0 ? pre[x] = find(pre[x]) : x;
        };
        long long ans = 0, cnt = 0;
        for (int i = 0; i < m; ++i) {
            int p_u = find(lines[i].u);
            int p_v = find(lines[i].v);
            if (p_u == p_v) {
                continue;
            }
            pre[p_u] = p_v;
            ans += lines[i].value;
            ++cnt;
        }
        if (cnt == n - 1) {
            std::cout << ans;
        } else {
            std::cout << "No solution.";
        }
        std::cout << std::endl;
    }
    return 0;
}
