class Solution {
    std::vector<std::vector<int>> ans_;

    void dfs(const std::vector<std::pair<int, int>> &candidates, int res, std::vector<int> &line, int index)
    {
        if (!res) {
            ans_.push_back(line);
            return ;
        }
        for (int i = index; i < (int)candidates.size(); ++i) {
            for (int k = 1; k <= candidates[i].second
                && res - candidates[i].first * k >= 0; ++k) {
                for (int j = 0; j < k; ++j) {
                    line.push_back(candidates[i].first);
                }
                dfs(candidates, res - candidates[i].first * k, line, i + 1);
                for (int j = 0; j < k; ++j) {
                    line.pop_back();
                }
            }
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        ans_.clear();

        std::vector<std::pair<int, int>> candidates2;
        std::sort(candidates.begin(), candidates.end());
        for (const auto &n : candidates) {
            if (candidates2.empty() || candidates2.back().first != n) {
                candidates2.emplace_back(n, 1);
            } else {
                ++candidates2.rbegin()->second;
            }
        }
        std::vector<int> line;
        dfs(candidates2, target, line, 0);

        return ans_;
    }
};
