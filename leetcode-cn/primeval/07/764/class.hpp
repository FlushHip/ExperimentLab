#include "headers.h"

class Solution {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        std::set<std::pair<int, int>> set_mines;
        for (const auto& v : mines) {
            set_mines.emplace(v[0], v[1]);
        }
        std::vector<std::vector<int>> dp_lhs(n, std::vector<int>(n)),
            dp_rhs(dp_lhs), dp_uhs(dp_lhs), dp_dhs(dp_lhs);
        for (int i = 0; i < n; ++i) {
            dp_lhs[i][0] = set_mines.find({i, 0}) == set_mines.end();
            dp_rhs[i][n - 1] = set_mines.find({i, n - 1}) == set_mines.end();
            dp_uhs[0][i] = set_mines.find({0, i}) == set_mines.end();
            dp_dhs[n - 1][i] = set_mines.find({n - 1, i}) == set_mines.end();
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                dp_lhs[i][j] = set_mines.find({i, j}) != set_mines.end()
                    ? 0
                    : dp_lhs[i][j - 1] + 1;
                dp_rhs[i][n - j - 1] =
                    set_mines.find({i, n - j - 1}) != set_mines.end()
                    ? 0
                    : dp_rhs[i][n - j] + 1;
                dp_uhs[j][i] = set_mines.find({j, i}) != set_mines.end()
                    ? 0
                    : dp_uhs[j - 1][i] + 1;
                dp_dhs[n - j - 1][i] =
                    set_mines.find({n - j - 1, i}) != set_mines.end()
                    ? 0
                    : dp_dhs[n - j][i] + 1;
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ans = std::max(ans,
                    std::min(std::min(dp_lhs[i][j], dp_rhs[i][j]),
                        std::min(dp_uhs[i][j], dp_dhs[i][j])));
            }
        }
        return ans;
    }
};
