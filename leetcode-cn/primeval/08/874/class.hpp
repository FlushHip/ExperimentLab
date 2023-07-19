#include "headers.h"

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        std::set<std::pair<int, int>> ust;
        for (auto& obstacle : obstacles) {
            ust.emplace(obstacle[0], obstacle[1]);
        }
        std::array<std::array<int, 2>, 4> dir{{
            {1, 0},
            {0, 1},
            {-1, 0},
            {0, -1},
        }};
        struct peo_t {
            int x, y;
            int d;
        } peo{0, 0, 1};

        int ans = 0;
        for (auto cmd : commands) {
            if (cmd == -1) {
                peo.d = (peo.d - 1 + 4) % 4;
            } else if (cmd == -2) {
                peo.d = (peo.d + 1) % 4;
            } else {
                for (int i = 0; i < cmd; ++i) {
                    int n_x = peo.x + dir[peo.d][0];
                    int n_y = peo.y + dir[peo.d][1];
                    if (ust.count({n_x, n_y})) {
                        break;
                    }
                    peo.x = n_x;
                    peo.y = n_y;
                    ans = std::max(ans, peo.x * peo.x + peo.y * peo.y);
                }
            }
        }
        return ans;
    }
};
