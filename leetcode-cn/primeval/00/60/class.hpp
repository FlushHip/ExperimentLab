#include "headers.h"

class Solution {
public:
    string getPermutation(int n, int k) {
        static std::array<int, 9> f = [] {
            std::array<int, 9> ret;
            ret[0] = 1;
            for (int i = 1; i < 9; ++i) {
                ret[i] = ret[i - 1] * i;
            }
            return ret;
        }();
        std::string ans;
        std::vector<bool> used(n + 1, false);
        for (int L = n; L > 0; --L) {
            int index = (k + f[L - 1] - 1) / f[L - 1];
            int digit = 1, sum = 0;
            for (int i = 1; i <= n; ++i) {
                sum += !used[i];
                if (sum == index) {
                    digit = i;
                    break;
                }
            }
            used[digit] = true;
            ans.push_back('0' + digit);
            k = (k - 1) % f[L - 1] + 1;
        }
        return ans;
    }
};
