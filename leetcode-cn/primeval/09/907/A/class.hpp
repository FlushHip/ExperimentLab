#include "headers.h"

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        struct node {
            int lhs, rhs;
        };
        std::vector<node> nodes(n);

        // lhs
        std::stack<int> max_st;
        for (int i = 0; i < n; ++i) {
            while (!max_st.empty() && arr[max_st.top()] >= arr[i]) {
                max_st.pop();
            }
            nodes[i].lhs = max_st.empty() ? 0 : max_st.top() + 1;
            max_st.push(i);
        }

        // rhs
        while (!max_st.empty()) {
            max_st.pop();
        }
        for (int i = n - 1; i >= 0; --i) {
            while (!max_st.empty() && arr[max_st.top()] > arr[i]) {
                max_st.pop();
            }
            nodes[i].rhs = max_st.empty() ? n - 1 : max_st.top() - 1;
            max_st.push(i);
        }
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = (ans +
                      (i - nodes[i].lhs + 1ll) * (nodes[i].rhs - i + 1) *
                          arr[i]) %
                smod;
        }
        return ans;
    }

private:
    constexpr static long long smod = 1e9 + 7;
};
