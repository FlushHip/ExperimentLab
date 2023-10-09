#include "headers.h"

class Solution {
public:
    int passThePillow(int n, int time) {
        time %= 2 * (n - 1);
        return time > n - 1 ? n - (time - (n - 1)) : 1 + time;
    }
};
