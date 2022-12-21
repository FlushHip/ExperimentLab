#include <algorithm>
#include "headers.h"

class Solution {
public:
    int secondHighest(string s) {
        auto end = std::partition(
            s.begin(), s.end(), [](char c) { return std::isdigit(c); });
        std::sort(s.begin(), end);
        auto u_end = std::unique(s.begin(), end);
        return u_end - s.begin() < 2 ? -1 : (*(u_end - 2) - '0');
    }
};
