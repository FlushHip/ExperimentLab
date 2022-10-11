#include "headers.h"

class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        int cnt = 0;
        for (int i = 0; i < static_cast<int>(s1.size()); ++i) {
            cnt += static_cast<int>(s1[i] != s2[i]);
        }
        if (cnt != 0 && cnt != 2) {
            return false;
        }
        std::sort(s1.begin(), s1.end());
        std::sort(s2.begin(), s2.end());
        return s1 == s2;
    }
};
