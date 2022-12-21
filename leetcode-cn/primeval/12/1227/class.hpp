#include "headers.h"

// https://leetcode.cn/problems/airplane-seat-assignment-probability/solution/1227-fei-ji-zuo-wei-fen-pei-gai-lu-by-yukarun/
class Solution {
public:
    double nthPersonGetsNthSeat(int n) { return n == 1 ? 1 : 0.5; }
};
