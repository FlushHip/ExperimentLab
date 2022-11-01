#include "headers.h"

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int n = heightMap.size(), m = heightMap[0].size();
        std::vector<std::vector<bool>> used(n, std::vector<bool>(m, false));
        struct node {
            int h;
            int x, y;
            bool operator<(const node& other) const { return h > other.h; }
        };
        std::priority_queue<node> que;
        for (int i = 0; i < n; ++i) {
            used[i][0] = used[i][m - 1] = true;
            que.push(node{heightMap[i][0], i, 0});
            que.push(node{heightMap[i][m - 1], i, m - 1});
        }
        for (int i = 0; i < m; ++i) {
            used[0][i] = used[n - 1][i] = true;
            que.push(node{heightMap[0][i], 0, i});
            que.push(node{heightMap[n - 1][i], n - 1, i});
        }
        int ans = 0;
        while (!que.empty()) {
            auto [min_h, x, y] = que.top();
            que.pop();
            static std::array<std::array<int, 2>, 4> sdir{{
                {0, 1},
                {0, -1},
                {1, 0},
                {-1, 0},
            }};
            for (auto [dir_x, dir_y] : sdir) {
                int row = x + dir_x;
                int col = y + dir_y;
                if (row >= 0 && row < n && col >= 0 && col < m &&
                    !used[row][col]) {
                    ans += std::max(heightMap[row][col], min_h) -
                        heightMap[row][col];
                    used[row][col] = true;
                    que.push(
                        node{std::max(heightMap[row][col], min_h), row, col});
                }
            }
        }
        return ans;
    }
};
