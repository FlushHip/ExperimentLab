#include "headers.h"

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        constexpr int invalid = 0x3f3f3f3f;
        const int n = matrix.size(), m = matrix[0].size();
        int x = 0, y = 0, dir = 0;
        std::vector<int> ans;
        ans.reserve(n * m);
        for (int i = 0; i < n * m; ++i) {
            ans.push_back(matrix[x][y]);
            matrix[x][y] = invalid;
            if (dir == 0) {
                ++y;
                if (y == m || invalid == matrix[x][y]) {
                    dir = 1;
                    ++x;
                    --y;
                }
            } else if (dir == 1) {
                ++x;
                if (x == n || invalid == matrix[x][y]) {
                    dir = 2;
                    --y;
                    --x;
                }
            } else if (dir == 2) {
                --y;
                if (y == -1 || invalid == matrix[x][y]) {
                    dir = 3;
                    --x;
                    ++y;
                }
            } else {
                --x;
                if (x == -1 || invalid == matrix[x][y]) {
                    dir = 0;
                    ++y;
                    ++x;
                }
            }
        }
        return ans;
    }
};
