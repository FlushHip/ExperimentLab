#include "headers.h"

class Solution {
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.size();
        std::vector<int> ans(n, 0), sums(n);
        sums[0] = boxes[0] == '1';
        for (int i = 1; i < n; ++i) {
            sums[i] = sums[i - 1] + (boxes[i] == '1');
            ans[0] += boxes[i] == '1' ? i : 0;
        }
        for (int i = 1; i < n; ++i) {
            ans[i] = ans[i - 1] + sums[i - 1] - (sums[n - 1] - sums[i - 1]);
        }
        return ans;
    }
};
