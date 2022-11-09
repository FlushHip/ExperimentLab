#include "headers.h"

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> ans(n, -1);
        std::stack<int> st;
        for (int i = 0; i < 2 * n; ++i) {
            while (!st.empty() &&
                (i - st.top() >= n || nums[st.top() % n] < nums[i % n])) {
                ans[st.top() % n] = i - st.top() >= n ? -1 : nums[i % n];
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }
};
