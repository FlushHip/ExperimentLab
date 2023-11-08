#include "headers.h"

class Solution {
public:
    int findTheLongestBalancedSubstring(string s) {
        int n = static_cast<int>(s.size());
        std::vector<int> lhs_0(n, 0), rhs_1(n, 0);
        lhs_0[0] = s.front() == '0';
        rhs_1[n - 1] = s.back() == '1';
        for (int i = 1; i < n; ++i) {
            lhs_0[i] = s[i] == '0' ? lhs_0[i - 1] + 1 : 0;
        }
        for (int i = n - 2; i >= 0; --i) {
            rhs_1[i] = s[i] == '1' ? rhs_1[i + 1] + 1 : 0;
        }
        int ret = 0;
        for (int i = 1; i < n; ++i) {
            ret = std::max(ret, 2 * std::min(lhs_0[i - 1], rhs_1[i]));
        }
        return ret;
    }
};
