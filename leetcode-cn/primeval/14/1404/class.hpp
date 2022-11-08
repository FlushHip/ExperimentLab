#include "headers.h"

class Solution {
public:
    int numSteps(string s) {
        int n = s.size(), ans = 0;
        std::reverse(s.begin(), s.end());
        int begin = 0;
        while (begin < n - 1) {
            char c = ((s[begin] - '0') ^ 1) + '0';
            auto pos = s.find_first_of(c, begin);
            pos = pos == std::string::npos ? n : pos;
            if (s[begin] == '0') {
                ans += pos - begin;
            } else {
                ans += pos - begin + 1;
                if (pos != n) {
                    s[pos] = '1';
                }
            }
            begin = pos;
        }
        return ans;
    }
};
