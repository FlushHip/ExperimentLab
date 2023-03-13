#include "headers.h"

class Solution {
public:
    vector<int> grayCode(int n) {
        std::vector<int> ans(1 << n, 0);
        for (int i = 1, size = 1; i <= n; ++i, size <<= 1) {
            for (int j = size - 1, k = size; j >= 0; --j, ++k) {
                ans[k] = ans[j] | (1 << (i - 1));
            }
        }
        return ans;
    }
};
