#include "headers.h"

class Solution {
public:
    int reinitializePermutation(int n) {
        int index = 1, ans = 0;
        do {
            if (index % 2) {
                index = n / 2 + (index - 1) / 2;
            } else {
                index = index / 2;
            }
            ++ans;
        } while (index != 1);
        return ans;
    }
};
