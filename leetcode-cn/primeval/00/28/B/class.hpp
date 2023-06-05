#include "headers.h"

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = static_cast<int>(haystack.size()),
            m = static_cast<int>(needle.size());
        std::vector<int> next(m);
        next[0] = 0;
        for (int i = 1, j = 0; i < m; ++i) {
            while (j > 0 && needle[i] != needle[j]) {
                j = next[j - 1];
            }
            if (needle[i] == needle[j]) {
                ++j;
            }
            next[i] = j;
        }
        for (int i = 0, j = 0; i < n; ++i) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                ++j;
            }
            if (j == m) {
                return i - m + 1;
            }
        }
        return -1;
    }
};
