#include "headers.h"

class Solution {
public:
    int magicalString(int n) {
        if (n < 3) {
            return 1;
        }
        std::vector<int> line(n);
        line[0] = 1;
        line[1] = 2;
        for (int i = 1, j = 1, pre = 1; i < n; ++i) {
            int now = ((pre - 1) ^ 1) + 1;
            for (int k = 0; k < line[i] && j < n; ++k) {
                line[j++] = now;
            }
            pre = now;
            if (!(j < n)) {
                break;
            }
        }
        return std::count(line.begin(), line.end(), 1);
    }
};
