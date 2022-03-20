class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        int n = static_cast<int>(patience.size());
        std::vector<std::vector<int>> mp(n);
        for (const auto &edge : edges) {
            auto from = edge[0], to = edge[1];
            mp[from].push_back(to);
            mp[to].push_back(from);
        }

        std::vector<bool> used(n, false);
        std::vector<int> dis(n, std::numeric_limits<int>::max());
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> que;
        que.emplace(dis[0] = 0, 0);

        while (!que.empty()) {
            auto [d, id] = que.top();
            que.pop();
            used[id] = true;
            for (auto to : mp[id]) {
                if (!used[to] && dis[to] > dis[id] + 1) {
                    dis[to] = dis[id] + 1;
                    que.emplace(dis[to], to);
                }
            }
        }

        int ans = 0;
        for (int i = 1; i < n; ++i) {
            int T = 2 * dis[i];
            if (T > patience[i]) {
                T = ((T - 1) / patience[i]) * patience[i] + T;
            }
            ++T;
            ans = std::max(ans, T);
        }

        return ans;
    }
};
