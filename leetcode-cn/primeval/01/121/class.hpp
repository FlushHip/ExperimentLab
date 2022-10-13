class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = (int)prices.size();
        int go = std::numeric_limits<int>::max(), ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = std::max(ans, prices[i] - go);
            go = std::min(go, prices[i]);
        }
        return ans;
    }
};
