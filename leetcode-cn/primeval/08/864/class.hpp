#include "headers.h"

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int n = grid.size(), m = grid[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '@') {
                    return bfs(i, j, grid, n, m);
                }
            }
        }
        return 0;
    }

private:
    int bfs(int start_x,
        int start_y,
        const std::vector<std::string>& grid,
        int n,
        int m) {
        int num_keys = std::accumulate(grid.begin(), grid.end(), 0,
                           [](int init, std::string_view line) {
                               return init +
                                   std::count_if(line.begin(), line.end(),
                                       [](char c) { return std::isalpha(c); });
                           }) /
            2;
        std::vector<std::vector<std::vector<bool>>> used(n,
            std::vector<std::vector<bool>>(
                m, std::vector<bool>(1U << num_keys)));
        struct node {
            int x, y, step;
            unsigned int mask;
        };
        std::queue<node> que;
        que.push(node{start_x, start_y, 0, 0});
        used[start_x][start_y][0] = true;
        while (!que.empty()) {
            auto now_node = que.front();
            que.pop();

            static std::array<std::array<int, 2>, 4> sdir{{
                {0, 1},
                {0, -1},
                {1, 0},
                {-1, 0},
            }};

            int step = now_node.step + 1;
            for (auto [offset_x, offset_y] : sdir) {
                int x = now_node.x + offset_x;
                int y = now_node.y + offset_y;
                if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == '#') {
                    continue;
                }
                if ((grid[x][y] == '.' || grid[x][y] == '@') &&
                    !used[x][y][now_node.mask]) {
                    used[x][y][now_node.mask] = true;
                    que.push(node{x, y, step, now_node.mask});
                }
                if (std::islower(grid[x][y])) {
                    int index = grid[x][y] - 'a';
                    unsigned mask = now_node.mask | (1U << index);
                    if (!used[x][y][mask]) {
                        if (mask + 1 == (1U << num_keys)) {
                            return step;
                        }
                        used[x][y][mask] = true;
                        que.push(node{x, y, step, mask});
                    }
                }
                if (std::isupper(grid[x][y])) {
                    int index = grid[x][y] - 'A';
                    if (!used[x][y][now_node.mask] &&
                        now_node.mask & (1U << index)) {
                        used[x][y][now_node.mask] = true;
                        que.push(node{x, y, step, now_node.mask});
                    }
                }
            }
        }
        return -1;
    }
};
