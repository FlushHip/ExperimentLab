class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        ans_.clear();

        std::vector<int> path;
        dfs(graph, path, 0);
        return ans_;
    }

    void dfs(const std::vector<std::vector<int>> &graph
        , std::vector<int> &path, unsigned int cur)
    {
        path.push_back(cur);
        if (cur + 1 == graph.size()) {
            ans_.push_back(path);
            path.pop_back();
            return;
        }

        for (const auto & v : graph[cur]) {
            dfs(graph, path, v);
        }
        path.pop_back();
    }
private:
    std::vector<std::vector<int>> ans_;
};
