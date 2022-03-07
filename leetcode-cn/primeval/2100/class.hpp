class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        auto fn = [](const std::vector<int> &security)
        {
            std::vector<int> dp(security.size(), 1);
            for (auto i = 1u; i < security.size(); ++i) {
                if (!(security[i - 1] < security[i])) {
                    dp[i] = dp[i - 1] + 1;
                }
            }
            return dp;
        };

        auto dp_r = fn(security), dp_l = fn(std::vector<int>(security.rbegin(), security.rend()));
        std::reverse(dp_l.begin(), dp_l.end());
        std::vector<int> ans;

        for (int i = time; i < ((int)security.size()) - time; ++i) {
            if (dp_r[i] > time && dp_l[i] > time) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
