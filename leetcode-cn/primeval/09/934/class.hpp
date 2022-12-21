#include "headers.h"

class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size(), c = 2;
        for (int row = 0; row < n && c != 4; ++row) {
            for (int col = 0; col < n && c != 4; ++col) {
                if (grid[row][col] == 1) {
                    dfs(grid, row, col, c++);
                }
            }
        }
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                if (grid[row][col] == 2) {
                    return bfs(grid, row, col);
                }
            }
        }
        return 0;
    }

private:
    int bfs(std::vector<std::vector<int>>& grid, int row, int col) {
        int n = grid.size();
        using node = std::tuple<int, int, int>;
        auto cmp = [](const node& lhs, const node& rhs) {
            return std::greater<int>{}(std::get<2>(lhs), std::get<2>(rhs));
        };
        std::priority_queue<node, std::vector<node>, decltype(cmp)> st(cmp);
        st.emplace(row, col, 0);
        grid[row][col] = -1;
        while (!st.empty()) {
            auto [row, col, cnt] = st.top();
            st.pop();
            for (int i = 0; i < 4; ++i) {
                int x = row + dir[i][0];
                int y = col + dir[i][1];
                if (x < 0 || y < 0 || x >= n || y >= n || !(grid[x][y] + 1)) {
                    continue;
                }
                if (grid[x][y] == 3) {
                    return cnt;
                } else {
                    st.emplace(x, y, cnt + (grid[x][y] == 0 ? 1 : 0));
                    grid[x][y] = -1;
                }
            }
        }
        return 0;
    }

    void dfs(std::vector<std::vector<int>>& grid, int row, int col, int c) {
        int n = grid.size();
        grid[row][col] = c;
        for (int i = 0; i < 4; ++i) {
            int x = row + dir[i][0];
            int y = col + dir[i][1];
            if (x < 0 || y < 0 || x >= n || y >= n || grid[x][y] != 1) {
                continue;
            }
            dfs(grid, x, y, c);
        }
    }

    constexpr static std::array<std::array<int, 2>, 4> dir{{
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
    }};
};
