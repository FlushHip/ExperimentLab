class Solution {
public:
    bool isValid(string s) {
        std::stack<char> st;
        for (const auto c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
                continue;
            }
            if (!st.empty() && ((c == ')' && st.top() == '(')
                || (c == ']' && st.top() == '[')
                || (c == '}' && st.top() == '{'))) {
                st.pop();
                continue;
            }
            return false;
        }
        return st.empty();
    }
};
