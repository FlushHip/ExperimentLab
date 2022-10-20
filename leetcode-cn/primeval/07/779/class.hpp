#include "headers.h"

class Solution {
public:
    int kthGrammar(int n, int k) {
        if (n == 1) {
            return 0;
        }
        int pre = kthGrammar(n - 1, std::max((k + 1) >> 1, 1));
        return pre == 0 ? (k & 1 ? 0 : 1) : (k & 1 ? 1 : 0);
    }
};
