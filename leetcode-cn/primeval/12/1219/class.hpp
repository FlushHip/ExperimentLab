class Solution {
    int dfs(const std::vector<std::vector<int>> &grid,
        std::vector<std::vector<bool>> &used,
        int n, int m, int i, int j) {
        static int dir_x[] = { 0, 0, 1, -1 };
        static int dir_y[] = { 1, -1, 0, 0 };

        int ans = 0;
        for (int k = 0; k < 4; ++k) {
            int x = i + dir_x[k];
            int y = j + dir_y[k];
            if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] && !used[x][y]) {
                used[x][y] = true;
                int res = dfs(grid, used, n, m, x, y);
                ans = std::max(ans, res);
                used[x][y] = false;
            }
        }
        return grid[i][j] + ans;
    }
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int n = (int)grid.size(), m = (int)grid.front().size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j]) {
                    std::vector<std::vector<bool>> used(n, std::vector<bool>(m, false));
                    used[i][j] = true;
                    int sum = dfs(grid, used, n, m, i, j);
                    ans = std::max(ans, sum);
                }
            }
        }
        return ans;
    }
};
