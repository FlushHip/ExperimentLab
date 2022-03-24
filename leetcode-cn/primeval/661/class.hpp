class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        int n = (int)img.size(), m = (int)img[0].size();
        std::vector<std::vector<int>> ans(n, std::vector<int>(m, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int cnt = 0, sum = 0;
                for (int x = i - 1; x <= i + 1; ++x) {
                    for (int y = j - 1; y <= j + 1; ++y) {
                        if (x < 0 || x >= n || y < 0 || y >= m) continue;
                        ++cnt;
                        sum += img[x][y];
                    }
                }
                ans[i][j] = sum / cnt;
            }
        }
        return ans;
    }
};
