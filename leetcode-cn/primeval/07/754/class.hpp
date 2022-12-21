#include "headers.h"

class Solution {
public:
    int reachNumber(int target) {
        if (target < 0) {
            target = -target;
        }
        int lhs = 0, rhs = 100000 + 1;
        while (lhs < rhs) {
            int mid = (rhs + lhs) / 2;
            long long t = (mid + 1ll) * mid / 2;
            if (t < target) {
                lhs = mid + 1;
            } else {
                rhs = mid;
            }
        }
        return (target - ((lhs + 1) * lhs / 2)) % 2 == 0 ? lhs
                                                         : lhs + 1 + (lhs % 2);
    }
};
