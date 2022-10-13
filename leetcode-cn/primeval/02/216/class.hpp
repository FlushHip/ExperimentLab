class Solution {
    std::vector<std::vector<int>> ans_;

    void dfs(int i, int res_num, int res_digit, std::vector<int> &line)
    {
        if (!res_num || !res_digit) {
            if (!res_num && !res_digit) {
                ans_.push_back(line);
            }
            return ;
        }

        for (int j = i; j < 10 && res_digit - j >= 0; ++j) {
            line.push_back(j);
            dfs(j + 1, res_num - 1, res_digit - j, line);
            line.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        ans_.clear();

        std::vector<int> line;
        dfs(1, k, n, line);

        return ans_;
    }
};
