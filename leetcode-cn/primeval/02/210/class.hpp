#include "headers.h"

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        std::vector<std::vector<int>> edges(numCourses);
        for (const auto& e : prerequisites) {
            edges[e[1]].emplace_back(e[0]);
        }
        std::vector<int> visit(
            numCourses, 0);  // 0: not visit, 1: visiting, 2: visited
        std::stack<int> line;
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
            line.emplace(u);
            return true;
        };
        std::vector<int> ans;
        for (int i = 0; i < numCourses; ++i) {
            if (!visit[i] && !fn(i)) {
                return ans;
            }
        }
        for (; !line.empty(); line.pop()) {
            ans.emplace_back(line.top());
        }
        return ans;
    }
};
