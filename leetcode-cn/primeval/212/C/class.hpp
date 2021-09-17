// TAG : 字典树 + 优化
class Solution {
public:
    struct TreeDir {
        std::string word;
        std::unordered_map<char, std::shared_ptr<TreeDir>> childs;
    };
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        auto root = std::make_shared<TreeDir>();
        for (const auto &word : words) {
            auto p = root;
            for (const auto c : word) {
                if (!p->childs.count(c)) {
                    p->childs[c] = std::make_shared<TreeDir>();
                }
                p = p->childs[c];
            }
            p->word = word;
        }

        int m = (int)board.size(), n = (int)board[0].size();
        std::vector<std::string> ans;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                dfs(root, board, i, j, ans);
            }
        }
        return ans;
    }

    void dfs(std::shared_ptr<TreeDir> root
        , std::vector<std::vector<char>> &board
        , int i, int j
        , std::vector<std::string> &ans) {

        char c = board[i][j];
        if (!root->childs.count(c)) {
            return ;
        }
        auto pre = root;
        root = root->childs[c];
        if (!root->word.empty()) {
            ans.emplace_back(root->word);
            root->word.clear();
        }
        if (root->childs.empty()) {
            return ;
        }

        int m = (int)board.size(), n = (int)board[0].size();
        int dx[] = { 1, -1, 0, 0 };
        int dy[] = { 0, 0, 1, -1 };

        board[i][j] = '#';
        for (int L = 0; L < 4; ++L) {
            int x = i + dx[L];
            int y = j + dy[L];
            if ((x >= 0 && x < m && y >= 0 && y < n)
                && board[x][y] != '#') {
                dfs(root, board, x, y, ans);
            }
        }
        board[i][j] = c;

        if (root->childs.empty()) {
            pre->childs.erase(c);
        }
    }
};
