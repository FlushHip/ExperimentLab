#include "headers.h"

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        int const size = static_cast<int>(digits.size());
        std::string str_n = std::to_string(n);
        int m = static_cast<int>(str_n.size());
        std::array<int, 10> f{1};
        for (int i = 1; i < 10; ++i) {
            f[i] = size * f[i - 1];
        }
        int ans = 0;
        for (int i = 1; i <= m - 1; ++i) {
            ans += f[i];
        }
        bool fi = false;
        for (int i = 0; i < m; ++i) {
            if (digits[0][0] > str_n[i]) {
                fi = true;
                break;
            }
            auto it = std::lower_bound(digits.begin(), digits.end(), str_n[i],
                [](const std::string& digit, int value) {
                    return digit[0] < value;
                });
            if (it != digits.end() && it->at(0) == str_n[i]) {
                ans += (it - digits.begin()) * f[m - i - 1];
            } else {
                ans += (it - digits.begin()) * f[m - i - 1];
                fi = true;
                break;
            }
        }
        return ans + (!fi);
    }
};
