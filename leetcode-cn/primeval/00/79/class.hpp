#include "headers.h"

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = static_cast<int>(board.size()),
            m = static_cast<int>(board[0].size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (board[i][j] == word.front() &&
                    dfs(board, word, i, j, n, m)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool dfs(std::vector<std::vector<char>>& board,
        std::string_view word,
        int x,
        int y,
        const int n,
        const int m) {
        if (word.size() == 1) {
            return true;
        }
        word.remove_prefix(1);
        struct raii_t {
            raii_t(std::vector<std::vector<char>>& board, int x, int y)
                : board(board), x(x), y(y), pre(board[x][y]) {
                board[x][y] = '-';
            }
            ~raii_t() { board[x][y] = pre; }
            std::vector<std::vector<char>>& board;
            int x, y;
            char pre;
        } raii(board, x, y);

        for (auto [dir_x, dir_y] : std::initializer_list<std::pair<int, int>>{
                 {1, 0},
                 {-1, 0},
                 {0, 1},
                 {0, -1},
             }) {
            int n_x = dir_x + x;
            int n_y = dir_y + y;
            if (n_x >= 0 && n_x < n && n_y >= 0 && n_y < m &&
                board[n_x][n_y] == word.front() &&
                dfs(board, word, n_x, n_y, n, m)) {
                return true;
            }
        }
        return false;
    }
};
