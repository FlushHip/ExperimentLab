#include "headers.h"

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        std::vector<std::vector<std::pair<int, int>>> mp(n);
        for (auto& edge : edges) {
            mp[edge[0]].emplace_back(edge[1], edge[2] + 1);
            mp[edge[1]].emplace_back(edge[0], edge[2] + 1);
        }
        std::vector<int> dis(n, std::numeric_limits<int>::max());
        struct node_type {
            int to;
            int d;
        };
        auto cmp = [](const node_type& lhs, const node_type& rhs) {
            return lhs.d > rhs.d;
        };
        std::priority_queue<node_type, std::vector<node_type>, decltype(cmp)>
            que(cmp);
        que.emplace(node_type{0, 0});
        dis[0] = 0;

        while (!que.empty()) {
            auto [to, d] = que.top();
            que.pop();
            if (dis[to] < d) {
                continue;
            }
            for (auto [next, value] : mp[to]) {
                if (dis[to] + value < dis[next]) {
                    dis[next] = dis[to] + value;
                    que.emplace(node_type{next, dis[next]});
                }
            }
        }

        int ans = std::accumulate(edges.begin(), edges.end(),
            std::count_if(
                dis.begin(), dis.end(), [&](int d) { return d <= maxMoves; }),
            [&](int init, const std::vector<int>& edge) {
                return init +
                    std::min(edge[2],
                        std::max((maxMoves - dis[edge[0]]), 0) +
                            std::max(maxMoves - dis[edge[1]], 0));
            });

        return ans;
    }
};
