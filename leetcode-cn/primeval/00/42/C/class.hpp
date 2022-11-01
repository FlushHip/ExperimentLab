#include "headers.h"

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size(), ans = 0;
        int lhs = 0, rhs = n - 1, l_w = height[0], r_w = height[n - 1];
        while (rhs - lhs > 1) {
            if (l_w < r_w) {
                ++lhs;
                l_w = std::max(l_w, height[lhs]);
                ans += l_w - height[lhs];
            } else {
                --rhs;
                r_w = std::max(r_w, height[rhs]);
                ans += r_w - height[rhs];
            }
        }
        return ans;
    }
};
