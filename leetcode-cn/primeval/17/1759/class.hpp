#include "headers.h"

class Solution {
public:
    int countHomogenous(string s) {
        const long long mod = 1e9 + 7;
        long long ans = 0;
        int start = 0, n = s.size();
        for (auto end = s.find_first_not_of(s[start], start + 1); start != n;
             end = s.find_first_not_of(s[start], start + 1)) {
            if (end == std::string::npos) {
                end = n;
            }
            long long m = end - start;
            ans += m * (m + 1) / 2 % mod;
            ans %= mod;
            start = end;
        }
        return ans;
    }
};
