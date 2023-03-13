#include "headers.h"

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int lhs = 0, rhs = 0;
        int ans = 0;
        std::unordered_set<char> st;
        for (; rhs < n; ++rhs) {
            if (auto it = st.find(s[rhs]); it == st.end()) {
                ans = std::max(ans, rhs - lhs + 1);
            } else {
                while (lhs < rhs && s[lhs] != s[rhs]) {
                    st.erase(s[lhs]);
                    ++lhs;
                }
                ++lhs;
            }
            st.insert(s[rhs]);
        }
        return ans;
    }
};
