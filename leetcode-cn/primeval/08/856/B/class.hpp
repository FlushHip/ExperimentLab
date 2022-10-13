#include "headers.h"

class Solution {
public:
    int scoreOfParentheses(string s) {
        int dep = 1, ans = 0;
        for (int i = 1; i < static_cast<int>(s.size()); ++i) {
            if (s[i] == '(') {
                ++dep;
            } else {
                --dep;
                if (s[i - 1] == '(') {
                    ans += 1 << dep;
                }
            }
        }
        return ans;
    }
};
