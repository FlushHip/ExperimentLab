#include "headers.h"

class Solution {
public:
    bool digitCount(string num) {
        std::array<int, 10> hash_digit{0};
        for (char c : num) {
            ++hash_digit[c - '0'];
        }
        for (int i = 0; i < num.size(); ++i) {
            if (hash_digit[i] != num[i] - '0') {
                return false;
            }
        }
        return true;
    }
};
