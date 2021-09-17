class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        std::unordered_set<char> us;
        // -
        for (int i = 0; i < 9; ++i) {
            us.clear();
            for (int j = 0; j < 9; ++j) {
                char c = board[i][j];
                if (c != '.') {
                    if (us.count(c)) {
                        return false;
                    }
                    us.insert(c);
                }
            }
        }
        // |
        for (int i = 0; i < 9; ++i) {
            us.clear();
            for (int j = 0; j < 9; ++j) {
                char c = board[j][i];
                if (c != '.') {
                    if (us.count(c)) {
                        return false;
                    }
                    us.insert(c);
                }
            }
        }
        // +
        for (int I = 0; I < 9; I += 3) {
            for (int J = 0; J < 9; J += 3) {
                us.clear();
                for (int i = I; i < I + 3; ++i) {
                    for (int j = J; j < J + 3; ++j) {
                        char c = board[i][j];
                        if (c != '.') {
                            if (us.count(c)) {
                                return false;
                            }
                            us.insert(c);
                        }
                    }
                }
            }
        }
        return true;
    }
};
