#include "headers.h"

class Solution {
public:
    string maximumNumber(string num, vector<int>& change) {
        int idx = 0, n = static_cast<int>(num.size());
        for (; idx < n && num[idx] - '0' >= change[num[idx] - '0']; ++idx) {
        }
        for (; idx < n && num[idx] - '0' <= change[num[idx] - '0']; ++idx) {
            num[idx] = change[num[idx] - '0'] + '0';
        }
        return num;
    }
};
