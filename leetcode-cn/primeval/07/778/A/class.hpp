#include "headers.h"

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        std::vector<bool> used(n * n, false);
        std::vector<int> dis(n * n, std::numeric_limits<int>::max());
        std::priority_queue<std::pair<int, int>,
            std::vector<std::pair<int, int>>, std::greater<>>
            pri_que;
        pri_que.emplace(dis[0] = grid[0][0], 0);

        while (!pri_que.empty()) {
            auto [d, idx] = pri_que.top();
            pri_que.pop();
            used[idx] = true;

            if (idx == (n - 1) * n + n - 1) {
                return dis[idx];
            }

            int x = idx / n, y = idx % n;
            for (auto [dir_x, dir_y] :
                std::initializer_list<std::pair<int, int>>{
                    {0, 1},
                    {0, -1},
                    {1, 0},
                    {-1, 0},
                }) {
                int next_x = x + dir_x, next_y = y + dir_y;
                if (next_x >= 0 && next_x < n && next_y >= 0 && next_y < n &&
                    !used[next_x * n + next_y]) {
                    int next_d = std::max(grid[next_x][next_y], dis[idx]);
                    if (next_d < dis[next_x * n + next_y]) {
                        dis[next_x * n + next_y] = next_d;
                        pri_que.emplace(next_d, next_x * n + next_y);
                    }
                }
            }
        }
        return 0;
    }
};
