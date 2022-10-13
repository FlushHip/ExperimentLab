class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int sum = mean * (rolls.size() + n) - std::accumulate(rolls.begin(), rolls.end(), 0);
        int item = sum / n;
        if (item < 1 || std::ceil(sum * 1.0 / n) > 6) return {};
        std::vector<int> ans(n, item);
        for (int i = 0; i < sum - item * n; ++i) ++ans[i];
        return ans;
    }
};
