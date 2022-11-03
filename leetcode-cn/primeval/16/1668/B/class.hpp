#include "headers.h"

class Solution {
public:
    int maxRepeating(string sequence, string word) {
        int n = sequence.size(), m = word.size();
        if (m > n) {
            return 0;
        }
        std::vector<int> dp(n, 0);
        for (int i = m - 1; i < n; ++i) {
            if (std::equal(sequence.begin() + i + 1 - m,
                    sequence.begin() + i + 1, word.begin())) {
                dp[i] = i - m < 0 ? 1 : dp[i - m] + 1;
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};
