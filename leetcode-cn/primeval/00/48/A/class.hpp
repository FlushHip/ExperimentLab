class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = (int)matrix.size();
        for (int i = 0; i < n / 2; ++i) {
            for (int j = i; j < n - i - 1; ++j) {
                std::swap(matrix[i][j], matrix[j][n - i - 1]);
                std::swap(matrix[i][j], matrix[n - i - 1][n - j - 1]);
                std::swap(matrix[i][j], matrix[n - j - 1][i]);
            }
        }
    }
};
