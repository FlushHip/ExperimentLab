#include "headers.h"

class Solution {
public:
    bool queryString(string s, int n) {
        int len = static_cast<int>(s.size());
        std::unordered_set<int> ust;
        for (int i = 0; i < len; ++i) {
            int num = 0;
            for (int j = i; j < len; ++j) {
                num = num * 2 + s[j] - '0';
                if (num > 0 && num <= n) {
                    ust.insert(num);
                } else {
                    break;
                }
            }
        }
        return ust.size() == n;
    }
};
