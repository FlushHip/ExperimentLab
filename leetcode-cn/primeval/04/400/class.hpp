#include "headers.h"

class Solution {
public:
    int findNthDigit(int n) {
        long long cnt = 9, k = 1, sum = 0;
        for (; sum + cnt * k < n; cnt *= 10, ++k) {
            sum += cnt * k;
        }
        long long res = n - sum;
        long long begin = std::pow(10, k - 1), m = (res - 1) / k;
        begin += m;
        return std::to_string(begin)[(res - m * k - 1)] - '0';
    }
};
