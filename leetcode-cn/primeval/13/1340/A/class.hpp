class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = (int)arr.size();
        std::vector<int> dp(n, 1);
        std::vector<std::pair<int, int>> arr_sorted(n);
        std::transform(arr.begin(), arr.end(), arr_sorted.begin(), [index = 0](const auto num) mutable -> std::pair<int, int>
        {
            return { num, index++ };
        });
        std::sort(arr_sorted.begin(), arr_sorted.end());

        for (int i = 0; i < n; ++i) {
            int index = arr_sorted[i].second;
            for (int j = index - 1; j >= 0 && index - j <= d && arr[index] > arr[j]; --j) {
                dp[index] = std::max(dp[index], dp[j] + 1);
            }
            for (int j = index + 1; j < n && j - index <= d && arr[index] > arr[j]; ++j) {
                dp[index] = std::max(dp[index], dp[j] + 1);
            }
        }
        return *std::max_element(dp.begin(), dp.end());
    }
};
