class Solution {
public:
    int longestValidParentheses(std::string s) {
        int n = (int)s.size();
        if (!n) {
            return 0;
        }
        std::vector<int> dp(n, 0);
        for (int i = 1; i < n; ++i) {
            if (s[i - 1] == '(' && s[i] == ')') {
                dp[i] = i - 2 < 0 ? 2 : dp[i - 2] + 2;
            } else if (s[i - 1] == ')' && s[i] == ')') {
                dp[i] = i - dp[i - 1] - 1 < 0
                    ? 0
                    : s[i - dp[i - 1] - 1] != '('
                        ? 0
                        : i - dp[i - 1] - 2 < 0
                            ? dp[i - 1] + 2
                            : dp[i - dp[i - 1] - 2] + dp[i - 1] + 2;
            }
        }

        return *std::max_element(dp.begin(), dp.end());
    }
};
