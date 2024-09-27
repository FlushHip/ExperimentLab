#include "headers.h"

class Solution {
public:
    int takeCharacters(string s, int k) {
        int n = static_cast<int>(s.size());
        std::array<int, 3> last{0, 0, 0};
        for (char c : s) {
            ++last[c - 'a'];
        }
        if (std::any_of(last.begin(), last.end(), [=](int e) {
            return e < k;
        })) {
            return -1;
        }
        int lhs = 0, rhs = 0;
        int result = n;
        for (; rhs < n; ++rhs) {
            --last[s[rhs] - 'a'];
            while (lhs <= rhs && std::any_of(last.begin(), last.end(), [=] (int e) { return e < k; })) {
                ++last[s[lhs] - 'a'];
                ++lhs;
            }
            if (std::all_of(last.begin(), last.end(), [=](int e) {return e >= k;})) {
                result = std::min(result, n - (rhs - lhs + 1));
            }
        }
        return result;
    }
};
