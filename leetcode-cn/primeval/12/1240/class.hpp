#include "headers.h"

// https://leetcode.cn/link/?target=http://int-e.eu/~bf3/squares/view.html

class Solution {
public:
    int tilingRectangle(int n, int m) {
        std::vector<std::vector<bool>> matrix(n, std::vector<bool>(m));
        int ans = std::max(n, m);
        dfs(matrix, n, m, 0, ans, 0, 0);
        return ans;
    }

private:
    void dfs(std::vector<std::vector<bool>>& matrix,
        int n,
        int m,
        int cnt,
        int& ans,
        int i,
        int j) {
        if (i == n - 1 && j == m) {
            ans = std::min(ans, cnt);
            return;
        }
        if (cnt >= ans) {
            return;
        }
        if (j == m) {
            dfs(matrix, n, m, cnt, ans, i + 1, 0);
        } else {
            if (matrix[i][j]) {
                dfs(matrix, n, m, cnt, ans, i, j + 1);
            } else {
                // for (int L = 1; L <= std::min(n - i, m - j); ++L) {
                for (int L = std::min(n - i, m - j); L > 0;
                     --L) {  // optimization
                    if (auto valid =
                            [&](int i, int j, int L) {
                                return std::all_of(matrix.begin() + i,
                                    matrix.begin() + i + L, [j, L](auto& line) {
                                        return std::all_of(line.begin() + j,
                                            line.begin() + j + L,
                                            [](bool f) { return !f; });
                                    });
                            };
                        valid(i, j, L)) {
                        auto fill_b = [&](int i, int j, int L, bool f) {
                            std::for_each_n(
                                matrix.begin() + i, L, [j, L, f](auto& line) {
                                    std::fill_n(line.begin() + j, L, f);
                                });
                        };

                        fill_b(i, j, L, true);
                        dfs(matrix, n, m, cnt + 1, ans, i, j + L);
                        fill_b(i, j, L, false);
                    }
                }
            }
        }
    }
};
