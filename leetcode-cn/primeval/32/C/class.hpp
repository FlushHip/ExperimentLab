// TAG : 贪心双指针
class Solution {
public:
    int longestValidParentheses(std::string s) {
        int n = (int)s.size();
        if (!n) {
            return 0;
        }
        int ans1 = aux(s);
        std::reverse(s.begin(), s.end());
        std::transform(s.begin(), s.end()
            , s.begin(), [](const auto c) {
            return c == ')' ? '(' : ')';
        });
        int ans2 = aux(s);
        return std::max(ans1, ans2);
    }

    int aux(const std::string &s) {
        int ans = 0;
        int lhs = 0, rhs = 0;
        for (const auto c : s) {
            if (c == '(') {
                ++lhs;
            } else {
                ++rhs;
            }
            if (rhs > lhs) {
                lhs = rhs = 0;
            } else if (rhs == lhs) {
                ans = std::max(ans, 2 * rhs);
            }
        }
        return ans;
    }
};
