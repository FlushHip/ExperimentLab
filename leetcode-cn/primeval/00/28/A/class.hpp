#include "headers.h"

class Solution {
public:
    int strStr(string haystack, string needle) {
        std::unordered_map<char, int> shift;
        int n = static_cast<int>(needle.size());
        for (int i = 0; i < n; ++i) {
            shift[needle[i]] = n - i;
        }

        int m = static_cast<int>(haystack.size());
        for (int i = 0; i + n - 1 < m;) {
            bool f = true;
            for (int j = 0; j < n; ++j) {
                if (haystack[i + j] != needle[j]) {
                    f = false;
                    break;
                }
            }
            if (f) {
                return i;
            }
            if (i + n < m) {
                if (shift.count(haystack[i + n]) != 0) {
                    i += shift[haystack[i + n]];
                } else {
                    i += n + 1;
                }
            } else {
                break;
            }
        }
        return -1;
    }
};
