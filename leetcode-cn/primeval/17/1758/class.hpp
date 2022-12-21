#include "headers.h"

class Solution {
public:
    int minOperations(string s) {
        auto fn = [&s](char start) {
            int ret = 0;
            for (char c : s) {
                ret += start != c;
                start = ((start - '0') ^ 1) + '0';
            }
            return ret;
        };
        return std::min(fn('0'), fn('1'));
    }
};
