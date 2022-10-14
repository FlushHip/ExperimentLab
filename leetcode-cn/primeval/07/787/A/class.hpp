class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        n_ = n;
        dst_ = dst;
        buildMaps(flights);
        int ans = dfs(src, k + 1);
        return ans == std::numeric_limits<int>::max() >> 1 ?
            -1 : ans;
    }

    int dfs(int curPos, int dep)
    {
        if (curPos == dst_) {
            return 0;
        }
        int ans = std::numeric_limits<int>::max() >> 1;
        if (!dep) {
            return ans;
        }
        if (dp_[curPos].find(dep) != dp_[curPos].end()) {
            return dp_[curPos][dep];
        }

        for (const auto & edge : maps_[curPos]) {
            ans = std::min(ans,
                edge.second + dfs(edge.first, dep - 1));
        }

        return dp_[curPos][dep] = ans;
    }

    void buildMaps(const std::vector<std::vector<int>> &flights)
    {
        maps_.resize(n_);
        for (int i = 0; i < n_; ++i) {
            dp_[i] = { };
        }
        for (const auto & flight : flights) {
            maps_[flight[0]][flight[1]] = flight[2];
        }
    }

private:
    std::vector<std::map<int, int>> maps_;
    std::map<int, std::map<int, int>> dp_;
    int n_;
    int dst_;
};
