#include "headers.h"

class Solution {
public:
    int subtractProductAndSum(int n) {
        int lhs = 1, rhs = 0;
        for (; n; n /= 10) {
            int res = n % 10;
            lhs *= res;
            rhs += res;
        }
        return lhs - rhs;
    }
};
