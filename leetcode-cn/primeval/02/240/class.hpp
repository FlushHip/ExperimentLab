class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = (int)matrix.size(), m = (int)matrix[0].size();
        for (int r = 0, c = m - 1; r < n && c >= 0; ) {
            if (matrix[r][c] == target) {
                return true;
            }
            if (matrix[r][c] < target) {
                ++r;
            } else {
                --c;
            }
        }
        return false;
    }
};
