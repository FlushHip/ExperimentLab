#include "headers.h"

class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = static_cast<int>(books.size());
        std::vector<int> dp(n, std::numeric_limits<int>::max());
        for (int i = 0; i < n; ++i) {
            int sum = 0, max_value = 0;
            for (int j = i; j >= 0; j--) {
                if (sum + books[j][0] <= shelfWidth) {
                    sum += books[j][0];
                    max_value = std::max(max_value, books[j][1]);
                    dp[i] = std::min(
                        dp[i], (j - 1 >= 0 ? dp[j - 1] : 0) + max_value);
                } else {
                    break;
                }
            }
        }
        return dp[n - 1];
    }
};
