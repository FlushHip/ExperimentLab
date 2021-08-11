#include <iostream>
#include <vector>

class Solution {
public:
    int longestValidParentheses(std::string s) {
        int n = (int)s.size();
        if (!n) {
            return 0;
        }
        std::vector<unsigned int> dp(n + 1, 0);
        for (int i = 1; i < n; ++i) {
            if (s[i] == '(') {
                if (s[i - 1] == ')') {
                    dp[i] = dp[i - 1];
                }
            } else {
                if (s[i - 1] == '(') {
                    dp[i] = dp[i - 1] + 1;
                }
            }
        }

        return dp[n - 1] * 2;
    }
};

int main(int argc, char **argv)
{
    Solution sol{};

    std::cout << sol.longestValidParentheses(")()())") << std::endl;
    return 0;
}
