class Solution {
    void dfs(const std::vector<int> &arr, std::vector<int> &dp, int n, int d
        , int index) {
        if (dp[index] != -1) {
            return ;
        }

        dp[index] = 1;
        for (int j = index - 1; j >= 0 && index - j <= d && arr[index] > arr[j]; --j) {
            dfs(arr, dp, n, d, j);
            dp[index] = std::max(dp[index], dp[j] + 1);
        }
        for (int j = index + 1; j < n && j - index <= d && arr[index] > arr[j]; ++j) {
            dfs(arr, dp, n, d, j);
            dp[index] = std::max(dp[index], dp[j] + 1);
        }
    }
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = (int)arr.size();
        std::vector<int> dp(n, -1);
        for (int i = 0; i < n; ++i) {
            dfs(arr, dp, n, d, i);
        }
        return *std::max_element(dp.begin(), dp.end());
    }
};
