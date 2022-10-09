#include "headers.h"

class Solution {
public:
    int scoreOfParentheses(string s) {
        std::stack<int> st;
        st.push(0);
        for (char c : s) {
            if (c == '(') {
                st.push(0);
            } else {
                int score = 1;
                if (st.top() != 0) {
                    score = st.top() * 2;
                }
                st.pop();
                st.top() += score;
            }
        }
        return st.top();
    }
};
