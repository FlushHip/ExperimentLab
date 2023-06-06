#include "headers.h"

class Solution {
public:
    int numDecodings(string s) {
        int n = static_cast<int>(s.size());
        std::vector<int> dp(n, 0);
        dp[0] = s[0] == '0' ? 0 : 1;
        for (int i = 1; i < n; ++i) {
            if (s[i] != '0') {
                dp[i] = dp[i - 1];
            }
            if (int value = 0;
                std::from_chars(s.data() + i - 1, s.data() + i + 1, value),
                value <= 26 && value >= 10) {
                dp[i] += i - 2 >= 0 ? dp[i - 2] : 1;
            }
        }
        return dp[n - 1];
    }
};
