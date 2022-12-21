#include "headers.h"

class Solution {
public:
    string customSortString(string order, string s) {
        std::array<int, 26> index{-1};
        for (int i = 0; i < order.size(); ++i) {
            index[order[i] - 'a'] = i;
        }
        std::sort(s.begin(), s.end(), [&](char lhs, char rhs) {
            return index[lhs - 'a'] < index[rhs - 'a'];
        });
        return s;
    }
};
