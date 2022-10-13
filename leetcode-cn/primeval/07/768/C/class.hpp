#include "headers.h"

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        std::stack<int> st;
        for (int num : arr) {
            if (st.empty() || st.top() <= num) {
                st.push(num);
            } else {
                int top_max = st.top();
                while (!st.empty() && num < st.top()) {
                    st.pop();
                }
                st.push(top_max);
            }
        }
        return st.size();
    }
};
