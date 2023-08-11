#include "headers.h"

class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        int n = static_cast<int>(matrix.size()),
            m = static_cast<int>(matrix[0].size());
        std::vector<std::vector<int>> pre_sum(n, std::vector<int>(m, 0));
        pre_sum[0] = matrix[0];
        for (int j = 0; j < m; ++j) {
            for (int i = 1; i < n; ++i) {
                pre_sum[i][j] = pre_sum[i - 1][j] + matrix[i][j];
            }
        }
        std::vector<int> ans;
        int max_value = std::numeric_limits<int>::min();
        for (int r1 = 0; r1 < n; ++r1) {
            for (int r2 = r1; r2 < n; ++r2) {
                std::vector<int> line(m);
                for (int j = 0; j < m; ++j) {
                    line[j] =
                        pre_sum[r2][j] - (r1 == 0 ? 0 : pre_sum[r1 - 1][j]);
                }
                std::vector<int> dp(m), idx(m);
                dp[0] = line[0];
                idx[0] = 0;
                for (int j = 1; j < m; ++j) {
                    if (dp[j - 1] < 0) {
                        dp[j] = line[j];
                        idx[j] = j;
                    } else {
                        dp[j] = dp[j - 1] + line[j];
                        idx[j] = idx[j - 1];
                    }
                }
                for (int j = 0; j < m; ++j) {
                    if (max_value < dp[j]) {
                        max_value = dp[j];
                        ans = {r1, idx[j], r2, j};
                    }
                }
            }
        }
        return ans;
    }
};
