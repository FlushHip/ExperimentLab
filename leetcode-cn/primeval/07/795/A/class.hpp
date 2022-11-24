#include "headers.h"

class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int n = nums.size(), ans = 0;
        std::stack<int> st;
        nums.push_back(std::numeric_limits<int>::max());
        std::vector<int> lhs(n + 1);
        for (int i = 0; i <= n; ++i) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                if (nums[st.top()] >= left && nums[st.top()] <= right) {
                    ans += (st.top() - lhs[st.top()] + 1) * (i - st.top());
                }
                st.pop();
            }
            lhs[i] = st.empty() ? 0 : st.top() + 1;
            st.push(i);
        }
        return ans;
    }
};
