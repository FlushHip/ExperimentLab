#include "headers.h"

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size(), m = dungeon[0].size();
        dungeon[n - 1][m - 1] =
            dungeon[n - 1][m - 1] >= 0 ? 1 : 1 - dungeon[n - 1][m - 1];
        for (int i = n - 2; i >= 0; --i) {
            dungeon[i][m - 1] = dungeon[i][m - 1] < 0
                ? dungeon[i + 1][m - 1] - dungeon[i][m - 1]
                : (dungeon[i][m - 1] < dungeon[i + 1][m - 1]
                          ? dungeon[i + 1][m - 1] - dungeon[i][m - 1]
                          : 1);
        }
        for (int j = m - 2; j >= 0; --j) {
            dungeon[n - 1][j] = dungeon[n - 1][j] < 0
                ? dungeon[n - 1][j + 1] - dungeon[n - 1][j]
                : (dungeon[n - 1][j] < dungeon[n - 1][j + 1]
                          ? dungeon[n - 1][j + 1] - dungeon[n - 1][j]
                          : 1);
        }
        for (int i = n - 2; i >= 0; --i) {
            for (int j = m - 2; j >= 0; --j) {
                if (dungeon[i][j] < 0) {
                    dungeon[i][j] =
                        std::min(dungeon[i + 1][j], dungeon[i][j + 1]) -
                        dungeon[i][j];
                } else {
                    dungeon[i][j] = std::min(dungeon[i][j] < dungeon[i + 1][j]
                            ? dungeon[i + 1][j] - dungeon[i][j]
                            : 1,
                        dungeon[i][j] < dungeon[i][j + 1]
                            ? dungeon[i][j + 1] - dungeon[i][j]
                            : 1);
                }
            }
        }
        return dungeon[0][0];
    }
};
