class Solution {
    std::vector<std::vector<int>> ans_;

    void dfs(int index, int res, int n, std::vector<int> &line)
    {
        if (index == n + 1 && res) {
            return ;
        }
        if (!res) {
            ans_.push_back(line);
            return ;
        }

        for (int i = index; i <= n; ++i) {
            line.push_back(i);
            dfs(i + 1, res - 1, n, line);
            line.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        ans_.clear();

        std::vector<int> line;
        dfs(1, k, n, line);

        return ans_;
    }
};
