#include "headers.h"

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        constexpr int invalid = 0;
        int x = 0, y = 0, dir = 0;
        std::vector<std::vector<int>> ans(n, std::vector<int>(n, invalid));
        for (int i = 1; i <= n * n; ++i) {
            ans[x][y] = i;
            if (dir == 0) {
                ++y;
                if (y == n || ans[x][y]) {
                    dir = 1;
                    ++x;
                    --y;
                }
            } else if (dir == 1) {
                ++x;
                if (x == n || ans[x][y]) {
                    dir = 2;
                    --y;
                    --x;
                }
            } else if (dir == 2) {
                --y;
                if (y == -1 || ans[x][y]) {
                    dir = 3;
                    --x;
                    ++y;
                }
            } else {
                --x;
                if (x == -1 || ans[x][y]) {
                    dir = 0;
                    ++y;
                    ++x;
                }
            }
        }
        return ans;
    }
};
