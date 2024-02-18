#include "headers.h"

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        std::array<std::unordered_set<int>, 2> usts;
        int n = static_cast<int>(matrix.size()),
            m = static_cast<int>(matrix[0].size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (matrix[i][j] == 0) {
                    usts[0].insert(i);
                    usts[1].insert(j);
                }
            }
        }
        for (const auto row : usts[0]) {
            for (int j = 0; j < m; ++j) {
                matrix[row][j] = 0;
            }
        }
        for (const auto col : usts[1]) {
            for (int i = 0; i < n; ++i) {
                matrix[i][col] = 0;
            }
        }
    }
};
