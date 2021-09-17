// 超时
class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int m = (int)board.size(), n = (int)board[0].size();
        std::vector<std::string> ans;
        for (const auto & str : words) {
            bool f = false;
            for (int i = 0; i < m && !f; ++i) {
                for (int j = 0; j < n && !f; ++j) {
                    if (str[0] == board[i][j]) {
                        std::vector<std::vector<bool>> used(m, std::vector<bool>(n, false));
                        used[i][j] = true;
                        if (dfs(str, 1, board, used, i, j)) {
                            ans.emplace_back(str);
                            f = true;
                        }
                    }
                }
            }
        }
        return ans;
    }

    bool dfs(const std::string &word, int index
        , std::vector<std::vector<char>> &board
        , std::vector<std::vector<bool>> &used
        , int i, int j) {
        if (index == (int)word.size()) {
            return true;
        }
        int m = (int)board.size(), n = (int)board[0].size();
        int dx[] = { 1, -1, 0, 0 };
        int dy[] = { 0, 0, 1, -1 };
        for (int L = 0; L < 4; ++L) {
            int x = i + dx[L];
            int y = j + dy[L];
            if ((x >= 0 && x < m && y >= 0 && y < n)
                && board[x][y] == word[index]
                && !used[x][y]) {
                used[x][y] = true;
                if (dfs(word, index + 1, board, used, x, y)) {
                    return true;
                }
                used[x][y] = false;
            }
        }
        return false;
    }
};
