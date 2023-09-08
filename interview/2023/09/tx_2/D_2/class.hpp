#include <array>
#include <string>
#include <unordered_map>

#include <dbg.h>

class Solution {
public:
    int minOperations(std::string str) {
        int n = static_cast<int>(str.size());
        if (n == 1) {
            return 0;
        }
        int start = 0, end = 0;
        int one_to_zero = 0, zero_to_one = 0;
        for (; end < n;) {
            int sum = 0;
            if (str[start] == '0') {
                for (; end < n && str[end] == '0'; ++end) {
                    ++sum;
                }
                zero_to_one += (sum + 1) / 2;
                start = end;
            } else {
                for (; end < n && str[end] == '1'; ++end) {
                    ++sum;
                }
                one_to_zero += (sum + 1) / 2;
                start = end;
            }
        }
        return std::min(one_to_zero, zero_to_one);
    }
};
