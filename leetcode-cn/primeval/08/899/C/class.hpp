#include "headers.h"

class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k > 1) {
            std::sort(s.begin(), s.end());
            return s;
        }
        int size = static_cast<int>(s.size());
        int i = 0, j = 0;
        for (int m = 0; m < size && i < size && j < size;) {
            if (i == j) {
                ++i;
                continue;
            }
            if (s[(i + m) % size] == s[(j + m) % size]) {
                ++m;
            } else if (s[(i + m) % size] > s[(j + m) % size]) {
                i += m + 1;
                m = 0;
            } else {
                j += m + 1;
                m = 0;
            }
        }
        int index = std::min(i, j);
        return s.substr(index, size - index) + s.substr(0, index);
    }
};
