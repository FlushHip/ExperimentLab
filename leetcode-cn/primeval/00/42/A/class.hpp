#include "headers.h"

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size(), ans = 0;
        std::stack<int> min_st;
        for (int i = 0; i < n; ++i) {
            while (!min_st.empty() && height[min_st.top()] < height[i]) {
                int offset = min_st.top();
                min_st.pop();
                if (min_st.empty()) {
                    break;
                }
                int h = std::min(height[min_st.top()], height[i]);
                ans += (i - min_st.top() - 1) * (h - height[offset]);
            }
            min_st.push(i);
        }
        return ans;
    }
};
