#include "headers.h"

class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        std::sort(digits.begin(), digits.end());

        int n = digits.size();
        std::vector<std::array<int, 3>> dp(n, {0});
        std::vector<std::array<bool, 3>> choose(n, {false});

        dp[0][digits[0] % 3] = 1;
        choose[0][digits[0] % 3] = true;
        for (int i = 1; i < n; ++i) {
            int m = digits[i] % 3;
            if (dp[i - 1][(3 - m) % 3] == 0) {
                if (0 == m) {
                    dp[i][0] = 1;
                    choose[i][0] = true;
                } else {
                    dp[i][0] = dp[i - 1][0];
                }
            } else {
                if (dp[i - 1][0] > dp[i - 1][(3 - m) % 3] + 1) {
                    dp[i][0] = dp[i - 1][0];
                } else {
                    dp[i][0] = dp[i - 1][(3 - m) % 3] + 1;
                    choose[i][0] = true;
                }
            }
            if (dp[i - 1][(4 - m) % 3] == 0) {
                if (1 == m) {
                    dp[i][1] = 1;
                    choose[i][1] = true;
                } else {
                    dp[i][1] = dp[i - 1][1];
                }
            } else {
                if (dp[i - 1][1] > dp[i - 1][(4 - m) % 3] + 1) {
                    dp[i][1] = dp[i - 1][1];
                } else {
                    dp[i][1] = dp[i - 1][(4 - m) % 3] + 1;
                    choose[i][1] = true;
                }
            }
            if (dp[i - 1][(5 - m) % 3] == 0) {
                if (2 == m) {
                    dp[i][2] = 1;
                    choose[i][2] = true;
                } else {
                    dp[i][2] = dp[i - 1][2];
                }
            } else {
                if (dp[i - 1][2] > dp[i - 1][(5 - m) % 3] + 1) {
                    dp[i][2] = dp[i - 1][2];
                } else {
                    dp[i][2] = dp[i - 1][(5 - m) % 3] + 1;
                    choose[i][2] = true;
                }
            }
        }
        if (dp[n - 1][0] == 0) {
            return "";
        }
        std::vector<int> line;
        for (int i = n - 1, begin = 0; i >= 0; --i) {
            if (choose[i][begin]) {
                line.push_back(digits[i]);
                begin = (3 + begin - (digits[i] % 3)) % 3;
            }
        }
        std::string ans(line.size(), 0);
        std::transform(line.begin(), line.end(), ans.begin(),
            [](int c) { return '0' + c; });
        return std::all_of(
                   ans.begin(), ans.end(), [](char c) { return c == '0'; })
            ? "0"
            : ans;
    }
};
