#include <numeric>
#include "headers.h"

class Solution {
public:
    int countEven(int num) {
        int result = 0;
        for (int i = 1; i <= num; ++i) {
            auto str = std::to_string(i);
            result += std::accumulate(str.begin(), str.end(), 0,
                          [](int init, char c) { return c - '0' + init; }) %
                    2 ==
                0;
        }
        return result;
    }
};
