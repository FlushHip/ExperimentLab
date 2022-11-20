#include "headers.h"

class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        auto scroll = [](int i) { return i % 2; };
        std::vector<std::vector<double>> dp(
            2, std::vector<double>(query_row + 2, 0.0));
        dp[scroll(0)][0] = poured;
        for (int i = 0; i <= query_row; ++i) {
            std::fill_n(dp[scroll(i + 1)].begin(), i + 1, 0);
            for (int j = 0; j < i + 1; ++j) {
                if (dp[scroll(i)][j] > 1.0) {
                    auto next = (dp[scroll(i)][j] - 1.0) / 2;
                    dp[scroll(i)][j] = 1;
                    dp[scroll(i + 1)][j] += next;
                    dp[scroll(i + 1)][j + 1] += next;
                }
            }
        }
        return dp[scroll(query_row)][query_glass];
    }
};
