#include "headers.h"

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        if (n == 1) {
            return grid[0][0];
        }
        auto dp = grid;
        std::priority_queue<std::pair<int, int>> last_maxs;
        for (int i = 0; i < n; ++i) {
            if (last_maxs.size() < 2) {
                last_maxs.emplace(dp[0][i], i);
            } else {
                if (last_maxs.top().first > dp[0][i]) {
                    last_maxs.pop();
                    last_maxs.emplace(dp[0][i], i);
                }
            }
        }
        for (int i = 1; i < n; ++i) {
            auto back_min = last_maxs.top();
            last_maxs.pop();
            auto last_min = last_maxs.top();
            last_maxs.pop();
            for (int j = 0; j < n; ++j) {
                if (j != last_min.second) {
                    dp[i][j] = grid[i][j] + last_min.first;
                } else {
                    dp[i][j] = grid[i][j] + back_min.first;
                }

                if (last_maxs.size() < 2) {
                    last_maxs.emplace(dp[i][j], j);
                } else {
                    if (last_maxs.top().first > dp[i][j]) {
                        last_maxs.pop();
                        last_maxs.emplace(dp[i][j], j);
                    }
                }
            }
        }
        return last_maxs.pop(), last_maxs.top().first;
    }
};
