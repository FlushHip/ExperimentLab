class Solution {
    std::vector<std::vector<int>> ans_;

    void dfs(const std::vector<int> &candidates, int res, std::vector<int> &line, int index)
    {
        if (!res) {
            ans_.push_back(line);
            return ;
        }
        for (int i = index; i < (int)candidates.size() && res - candidates[i] >= 0; ++i) {
            line.push_back(candidates[i]);
            dfs(candidates, res - candidates[i], line, i);
            line.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        ans_.clear();

        std::sort(candidates.begin(), candidates.end());
        std::vector<int> line;
        dfs(candidates, target, line, 0);

        return ans_;
    }
};
