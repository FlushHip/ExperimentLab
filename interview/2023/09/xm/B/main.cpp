#include <functional>
#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}; std::cin >> n;) {
        std::string line;
        std::cin >> line;
        std::vector<std::vector<int>> prerequisites;
        for (auto begin = 0; begin != std::string::npos;) {
            auto pos = line.find(',', begin);
            std::string corse;
            if (pos != std::string::npos) {
                corse = line.substr(begin, pos - begin);
                begin = pos + 1;
            } else {
                corse = line.substr(begin);
                begin = pos;
            }
            auto mid_pos = corse.find(':');
            int x = std::stoi(corse.substr(0, mid_pos - 0));
            int y = std::stoi(corse.substr(mid_pos + 1));
            prerequisites.emplace_back(std::vector<int>{x, y});
        }
        dbg(prerequisites);

        std::vector<std::vector<int>> edges(n);
        for (const auto& e : prerequisites) {
            edges[e[1]].emplace_back(e[0]);
        }
        std::vector<int> visit(n, 0);  // 0: not visit, 1: visiting, 2: visited
        std::function<bool(int)> fn = [&](int u) -> bool {
            visit[u] = 1;
            for (auto v : edges[u]) {
                if (!visit[v]) {
                    if (!fn(v)) {
                        return false;
                    }
                } else if (visit[v] == 1) {
                    return false;
                }
            }
            visit[u] = 2;
            return true;
        };
        bool f = true;
        for (int i = 0; i < n; ++i) {
            if (!visit[i] && !fn(i)) {
                f = false;
                break;
            }
        }
        std::cout << (f ? 1 : 0) << std::endl;
    }
    return 0;
}
