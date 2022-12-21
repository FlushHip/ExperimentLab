#include "headers.h"

class Solution {
public:
    int maximumScore(int a, int b, int c) {
        if (a > b) {
            std::swap(a, b);
        }
        if (b > c) {
            std::swap(b, c);
        }
        if (a > b) {
            std::swap(a, b);
        }
        if (a + b <= c) {
            return a + b;
        }
        return (a + b + c) / 2;
    }
};
