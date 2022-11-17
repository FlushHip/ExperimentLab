#include "headers.h"

class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int n = s.size();
        std::vector<std::array<int, 26>> dp(n);
        dp[n - 1].fill(n);
        dp[n - 1][s[n - 1] - 'a'] = n - 1;
        for (int i = n - 2; i >= 0; --i) {
            dp[i] = dp[i + 1];
            dp[i][s[i] - 'a'] = i;
        }
        auto is_seq = [&dp, n](std::string_view s, std::string_view word) {
            int i = 0;
            for (int j = 0; j < s.size(); ++j) {
                if (dp[j][word[i] - 'a'] == n) {
                    break;
                }

                j = dp[j][word[i] - 'a'];
                ++i;
                if (i == word.size()) {
                    return true;
                }
            }
            return false;
        };

        return std::count_if(words.begin(), words.end(),
            [&s, &is_seq](std::string_view word) { return is_seq(s, word); });
    }
};
