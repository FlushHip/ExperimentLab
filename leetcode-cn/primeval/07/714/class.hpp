#include "headers.h"

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = static_cast<int>(prices.size());
        std::vector<int> dp_has(n), dp_no(n);
        dp_has[0] = -prices[0];
        dp_no[0] = 0;
        for (int i = 1; i < n; ++i) {
            dp_has[i] = std::max(dp_has[i - 1], dp_no[i - 1] - prices[i]);
            dp_no[i] = std::max(dp_no[i - 1], dp_has[i - 1] + prices[i] - fee);
        }
        return dp_no[n - 1];
    }
};
