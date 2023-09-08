#include <array>
#include <string>
#include <unordered_map>

#include <dbg.h>

class Solution {
public:
    int minOperations(std::string str) {
        int n = static_cast<int>(str.size());
        if (n == 1) {
            return 0;
        }
        std::vector<std::array<int, 2>> dp(n);
        dp[0][0] = str[0] == '0' ? 0 : n;
        dp[0][1] = str[0] == '1' ? 0 : n;
        auto get = [&dp](int x, int y) { return x < 0 ? 0 : dp[x][y]; };
        for (int i = 1; i < n; ++i) {
            if (str[i] == '0') {
                dp[i][0] =
                    std::min(dp[i - 1][0], (str[i - 1] == '1') + get(i - 2, 0));
                dp[i][1] = get(i - 2, 1) + 1;
            } else {
                dp[i][0] = get(i - 2, 0) + 1;
                dp[i][1] =
                    std::min(dp[i - 1][1], (str[i - 1] == '0') + get(i - 2, 1));
            }
        }
        dbg(str, dp);
        return std::min(dp[n - 1][0], dp[n - 1][1]);
    }
};
