class Solution {
public:
    int balancedStringSplit(string s) {
        int n = (int)s.size(), ans = 0;
        for (int lhs = 0, rhs = 0, i = 0; i < n; ++i) {
            if (s[i] == 'L') {
                ++lhs;
            } else {
                ++rhs;
            }
            if (lhs == rhs) {
                ++ans;
            }
        }
        return ans;
    }
};
