#include <unordered_map>
#include "headers.h"

class Solution {
public:
    bool digitCount(string num) {
        std::unordered_map<int, int> hash_digit;
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
