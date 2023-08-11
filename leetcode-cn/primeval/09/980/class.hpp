#include "headers.h"

class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        point_t start{};
        int num_rest{};
        int n = static_cast<int>(grid.size()),
            m = static_cast<int>(grid[0].size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] >= 0) {
                    ++num_rest;
                }
                if (grid[i][j] == 1) {
                    start = {i, j};
                }
            }
        }
        return dfs(grid, n, m, start, num_rest);
    }

private:
    struct point_t {
        int x;
        int y;
    };

    int dfs(std::vector<std::vector<int>>& grid,
        int n,
        int m,
        point_t point,
        int num_rest) {
        if (grid[point.x][point.y] == 2) {
            return num_rest == 1;
        }
        int pre = grid[point.x][point.y];
        grid[point.x][point.y] = -1;
        int ret = 0;
        for (auto [dir_x, dir_y] : std::initializer_list<std::pair<int, int>>{
                 {0, 1},
                 {0, -1},
                 {1, 0},
                 {-1, 0},
             }) {
            point_t next = {point.x + dir_x, point.y + dir_y};
            if (next.x >= 0 && next.x < n && next.y >= 0 && next.y < m &&
                grid[next.x][next.y] != -1) {
                ret += dfs(grid, n, m, next, num_rest - 1);
            }
        }
        grid[point.x][point.y] = pre;
        return ret;
    }
};
