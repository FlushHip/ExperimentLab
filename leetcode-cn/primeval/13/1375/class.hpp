#include "headers.h"

class Solution {
public:
    int numTimesAllBlue(vector<int>& flips) {
        int n = static_cast<int>(flips.size());
        std::vector<bool> line(n);
        int index = -1, ans = 0;
        for (int i = 0; i < n; ++i) {
            line[flips[i] - 1] = true;
            for (; index + 1 < n && line[index + 1]; ++index) {
            }
            if (index == i) {
                ++ans;
            }
        }
        return ans;
    }
};
