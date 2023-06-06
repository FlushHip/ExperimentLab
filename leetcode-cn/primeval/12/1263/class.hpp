#include "headers.h"

class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        constexpr int side_length = 21;
        struct position {
            int x{}, y{};
            bool operator==(const position& other) const {
                return x == other.x && y == other.y;
            }
        };

        int n = static_cast<int>(grid.size()),
            m = static_cast<int>(grid[0].size());
        position S, B, T;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 'S') {
                    S = {i, j};
                    grid[i][j] = '.';
                }
                if (grid[i][j] == 'B') {
                    B = {i, j};
                    grid[i][j] = '.';
                }
                if (grid[i][j] == 'T') {
                    T = {i, j};
                    grid[i][j] = '.';
                }
            }
        }
        struct context {
            position box, person;
            int step{};
            bool operator<(const context& other) const {
                return step > other.step;
            }
        };
        std::array<
            std::array<std::array<std::array<bool, side_length>, side_length>,
                side_length>,
            side_length>
            used{false};
        std::priority_queue<context> que;
        que.push(context{B, S, 0});
        used[B.x][B.y][S.x][S.y] = true;
        while (!que.empty()) {
            auto ctx = que.top();
            que.pop();

            for (auto [dir_x, dir_y] :
                std::initializer_list<std::pair<int, int>>{
                    {0, 1},
                    {0, -1},
                    {1, 0},
                    {-1, 0},
                }) {
                position p{dir_x + ctx.person.x, dir_y + ctx.person.y};
                if (p.x < 0 || p.x >= n || p.y < 0 || p.y >= m ||
                    grid[p.x][p.y] == '#') {
                    continue;
                }
                position b{ctx.box};
                int step = ctx.step;
                if (ctx.box == p) {
                    b.x += dir_x;
                    b.y += dir_y;
                    if (b.x < 0 || b.x >= n || b.y < 0 || b.y >= m ||
                        grid[b.x][b.y] == '#') {
                        continue;
                    }
                    ++step;
                }
                if (b == T) {
                    return step;
                }
                if (used[b.x][b.y][p.x][p.y]) {
                    continue;
                }
                used[b.x][b.y][p.x][p.y] = true;
                que.push(context{b, p, step});
            }
        }
        return -1;
    }
};
