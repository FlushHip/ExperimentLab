#include "headers.h"

class Solution {
public:
    int smallestRepunitDivByK(int k) {
        if (k % 2 == 0 || k % 5 == 0) {
            return -1;
        }
        int mod = 1 % k, ans = 1;
        while (mod != 0) {
            mod = (mod * 10 + 1) % k;
            ++ans;
        }
        return ans;
    }
};
