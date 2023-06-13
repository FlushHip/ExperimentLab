#include "headers.h"

class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        int n1 = static_cast<int>(str1.size()),
            n2 = static_cast<int>(str2.size());
        auto fn = [&](int x) {
            if (n1 % x != 0 || n2 % x != 0) {
                return false;
            }
            for (int start = x; start < n1; start += x) {
                if (std::string_view(str1.data(), x) !=
                    std::string_view(str1.data() + start, x)) {
                    return false;
                }
            }
            for (int start = 0; start < n2; start += x) {
                if (std::string_view(str1.data(), x) !=
                    std::string_view(str2.data() + start, x)) {
                    return false;
                }
            }
            return true;
        };
        int len = std::gcd(n1, n2);
        for (; len > 0 && !fn(len); --len) {
        }
        return {str1.data(), static_cast<size_t>(len)};
    }
};
