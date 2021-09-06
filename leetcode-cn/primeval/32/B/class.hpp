// TAG : 栈的妙用
class Solution {
public:
    int longestValidParentheses(std::string s) {
        int n = (int)s.size();
        if (!n) {
            return 0;
        }
        std::stack<int> st;
        st.push(-1);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                st.push(i);
                continue;
            }

            st.pop();
            if (st.empty()) {
                st.push(i);
            } else {
                ans = std::max(ans, i - st.top());
            }
        }
        return ans;
    }
};
