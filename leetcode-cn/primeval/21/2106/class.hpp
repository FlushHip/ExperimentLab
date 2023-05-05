#include "headers.h"

class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int top = std::max(fruits.back().front(), startPos);
        std::vector<int> arr(top + 1, 0);
        for (auto& line : fruits) {
            arr[line[0]] = line[1];
        }
        std::partial_sum(arr.begin(), arr.end(), arr.begin());
        int ans = 0;
        for (int x = 0; x <= k / 2; ++x) {
            int lhs = startPos - x, rhs = startPos + k - 2 * x;
            if (lhs < 0) {
                lhs = 0;
            }
            if (rhs > top) {
                rhs = top;
            }
            ans = std::max(ans, arr[rhs] - (lhs == 0 ? 0 : arr[lhs - 1]));

            rhs = startPos + x, lhs = startPos + 2 * x - k;
            if (lhs < 0) {
                lhs = 0;
            }
            if (rhs > top) {
                rhs = top;
            }
            ans = std::max(ans, arr[rhs] - (lhs == 0 ? 0 : arr[lhs - 1]));
        }
        return ans;
    }
};
