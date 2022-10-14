class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        maps_.clear();
        maps_.resize(n, std::vector<int>(n, inf_));
        for (int i = 0; i < n; ++i) {
            maps_[i][i] = 0;
        }
        for (const auto & edge : times) {
            maps_[edge[0] - 1][edge[1] - 1] = edge[2];
        }

        std::vector<int> dst(n, inf_);
        std::vector<bool> used(n, false);
        dst[k - 1] = 0;

        for (int i = 0; i < n; ++i) {
            int index = -1, tmp = inf_;
            for (int j = 0; j < n; ++j) {
                if (!used[j] && dst[j] < tmp) {
                    index = j;
                    tmp = dst[j];
                }
            }
            if (!(index + 1)) {
                break;
            }
            used[index] = true;
            for (int j = 0; j < n; ++j) {
                if (!used[j] && dst[index] + maps_[index][j] < dst[j]) {
                    dst[j] = dst[index] + maps_[index][j];
                }
            }
        }

        int ans = *std::max_element(dst.begin(), dst.end());
        return ans == inf_ ? -1 : ans;
    }
private:
    const int inf_ = std::numeric_limits<int>::max() / 2;
    std::vector<std::vector<int>> maps_;
};
