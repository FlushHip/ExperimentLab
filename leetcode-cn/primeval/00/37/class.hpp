#include "headers.h"

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        init(board);
        dfs(board, 0, 0);
    }

private:
    constexpr static int ntop = 9;
    std::array<std::bitset<ntop>, ntop> x_used_, y_used_, matrix_used_;

    void init(std::vector<std::vector<char>>& board) {
        x_used_.fill({});
        y_used_.fill({});
        matrix_used_.fill({});

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                    int n = board[i][j] - '0' - 1;
                    x_used_[i][n] = true;
                    y_used_[j][n] = true;
                    matrix_used_[(i / 3) * 3 + (j / 3)][n] = true;
                }
            }
        }
    }

    bool dfs(std::vector<std::vector<char>>& board, int x, int y) {
        if (x == ntop && y == 0) {
            return true;
        }
        if (y == ntop) {
            return dfs(board, x + 1, 0);
        }
        if (board[x][y] != '.') {
            return dfs(board, x, y + 1);
        }
        for (int i = 0; i < ntop; ++i) {
            if (!x_used_[x][i] && !y_used_[y][i] &&
                !matrix_used_[(x / 3) * 3 + (y / 3)][i]) {
                board[x][y] = i + 1 + '0';
                x_used_[x][i] = true;
                y_used_[y][i] = true;
                matrix_used_[(x / 3) * 3 + (y / 3)][i] = true;
                if (dfs(board, x, y + 1)) {
                    return true;
                }
                board[x][y] = '.';
                x_used_[x][i] = false;
                y_used_[y][i] = false;
                matrix_used_[(x / 3) * 3 + (y / 3)][i] = false;
            }
        }
        return false;
    }
};
