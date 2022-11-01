#include "headers.h"

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        struct node {
            int lhs, rhs;
        };
        std::vector<node> nodes(n);
        nodes[0].lhs = height[0];
        nodes[n - 1].rhs = height[n - 1];
        for (int i = 1; i < n; ++i) {
            nodes[i].lhs = std::max(nodes[i - 1].lhs, height[i]);
        }
        for (int i = n - 2; i >= 0; --i) {
            nodes[i].rhs = std::max(nodes[i + 1].rhs, height[i]);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += std::min(nodes[i].lhs, nodes[i].rhs) - height[i];
        }
        return ans;
    }
};
