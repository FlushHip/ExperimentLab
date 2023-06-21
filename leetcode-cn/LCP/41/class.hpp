#include "headers.h"

class Solution {
public:
    int flipChess(vector<string>& chessboard) {
        auto white_count = [](const std::vector<string>& chessboard) {
            return std::accumulate(chessboard.begin(), chessboard.end(), 0,
                [](int last, auto&& line) {
                    return last + std::count(line.begin(), line.end(), 'O');
                });
        };
        int n = static_cast<int>(chessboard.size()),
            m = static_cast<int>(chessboard[0].size());
        int init_cnt_white = white_count(chessboard);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (chessboard[i][j] == '.') {
                    auto aux_board{chessboard};
                    aux_board[i][j] = 'X';
                    bool change = true;
                    for (; change;) {
                        change = false;
                        for (int x = 0; x < n; ++x) {
                            for (int y = 0; y < m; ++y) {
                                if (aux_board[x][y] == 'O') {
                                    bool f = true;
                                    // row
                                    do {
                                        int k = x;
                                        for (--k;
                                             k >= 0 && aux_board[k][y] == 'O';
                                             --k) {
                                        }
                                        if (k < 0 || aux_board[k][y] != 'X') {
                                            f = false;
                                            break;
                                        }
                                        for (k = x + 1;
                                             k < n && aux_board[k][y] == 'O';
                                             ++k) {
                                        }
                                        if (k >= n || aux_board[k][y] != 'X') {
                                            f = false;
                                        }
                                    } while (false);
                                    if (f) {
                                        aux_board[x][y] = 'X';
                                        change = true;
                                        continue;
                                    }
                                    // col
                                    f = true;
                                    do {
                                        int k = y;
                                        for (--k;
                                             k >= 0 && aux_board[x][k] == 'O';
                                             --k) {
                                        }
                                        if (k < 0 || aux_board[x][k] != 'X') {
                                            f = false;
                                            break;
                                        }
                                        for (k = y + 1;
                                             k < m && aux_board[x][k] == 'O';
                                             ++k) {
                                        }
                                        if (k >= m || aux_board[x][k] != 'X') {
                                            f = false;
                                        }
                                    } while (false);
                                    if (f) {
                                        aux_board[x][y] = 'X';
                                        change = true;
                                        continue;
                                    }
                                    // bevel1
                                    f = true;
                                    do {
                                        int k1 = x, k2 = y;
                                        for (--k1, --k2; k1 >= 0 && k2 >= 0 &&
                                             aux_board[k1][k2] == 'O';
                                             --k1, --k2) {
                                        }
                                        if (k1 < 0 || k2 < 0 ||
                                            aux_board[k1][k2] != 'X') {
                                            f = false;
                                            break;
                                        }
                                        for (k1 = x + 1, k2 = y + 1; k1 < n &&
                                             k2 < m && aux_board[k1][k2] == 'O';
                                             ++k1, ++k2) {
                                        }
                                        if (k1 >= n || k2 >= m ||
                                            aux_board[k1][k2] != 'X') {
                                            f = false;
                                        }
                                    } while (false);
                                    if (f) {
                                        aux_board[x][y] = 'X';
                                        change = true;
                                        continue;
                                    }
                                    // bevel2
                                    f = true;
                                    do {
                                        int k1 = x, k2 = y;
                                        for (++k1, --k2; k1 < n && k2 >= 0 &&
                                             aux_board[k1][k2] == 'O';
                                             ++k1, --k2) {
                                        }
                                        if (k1 >= n || k2 < 0 ||
                                            aux_board[k1][k2] != 'X') {
                                            f = false;
                                            break;
                                        }
                                        for (k1 = x - 1, k2 = y + 1; k1 >= 0 &&
                                             k2 < m && aux_board[k1][k2] == 'O';
                                             --k1, ++k2) {
                                        }
                                        if (k1 < 0 || k2 >= m ||
                                            aux_board[k1][k2] != 'X') {
                                            f = false;
                                        }
                                    } while (false);
                                    if (f) {
                                        aux_board[x][y] = 'X';
                                        change = true;
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                    ans =
                        std::max(ans, init_cnt_white - white_count(aux_board));
                }
            }
        }
        return ans;
    }
};
