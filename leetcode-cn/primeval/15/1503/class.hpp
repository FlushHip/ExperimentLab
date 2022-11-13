#include "headers.h"

class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        return std::max(
            left.empty() ? 0 : *std::max_element(left.begin(), left.end()),
            right.empty() ? 0
                          : n - *std::min_element(right.begin(), right.end()));
    }
};
