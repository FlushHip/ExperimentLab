#include "headers.h"

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = static_cast<int>(grid.size()),
            m = static_cast<int>(grid[0].size());
        for (int ans = 0;; ++ans) {
            if (std::all_of(grid.begin(), grid.end(), [](auto&& line) {
                    return std::all_of(line.begin(), line.end(),
                        [](int g) { return g == 0 || g == 2; });
                })) {
                return ans;
            }
            auto next_grid = grid;
            bool change = false;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (grid[i][j] == 2) {
                        for (auto [dir_x, dir_y] :
                            std::initializer_list<std::array<int, 2>>{
                                {0, 1},
                                {0, -1},
                                {1, 0},
                                {-1, 0},
                            }) {
                            int n_i = dir_x + i, n_j = dir_y + j;
                            if (n_i >= 0 && n_i < n && n_j >= 0 && n_j < m &&
                                grid[n_i][n_j] == 1) {
                                change = true;
                                next_grid[n_i][n_j] = 2;
                            }
                        }
                    }
                }
            }
            if (!change) {
                break;
            }
            grid = next_grid;
        }
        return -1;
    }
};
