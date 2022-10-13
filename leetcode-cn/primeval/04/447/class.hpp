class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int n = (int)points.size(), ans = 0;
        for (int i = 0; i < n; ++i) {
            std::unordered_map<int, int> cnt;
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                int d2 = (points[i][0] - points[j][0]) * (points[i][0] - points[j][0])
                    + (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]);
                ++cnt[d2];
            }
            for (const auto & pr : cnt) {
                if (pr.second > 1) {
                    ans += pr.second * (pr.second - 1);
                }
            }
        }
        return ans;
    }
};
