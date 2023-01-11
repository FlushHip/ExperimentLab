#include "headers.h"

class Solution {
public:
    string crackSafe(int n, int k) {
        std::unordered_map<std::string, bool> lines;
        int top = static_cast<int>(std::pow(k, n));
        for (int i = 0; i < top; ++i) {
            std::array<char, 10> str{0};
            auto [ptr, _] =
                std::to_chars(str.data(), str.data() + str.size(), i, k);
            lines[std::string(n - (ptr - str.data()), '0') +
                std::string(str.data(), ptr)] = false;
        }
        std::string ans(n, '0');
        lines[ans] = true;
        for (int i = 1; i < top; ++i) {
            std::string start(ans.data() + i, ans.data() + i + n - 1);
            start.push_back('0');
            for (int suffix = k - 1; suffix >= 0; --suffix) {
                start.back() = suffix + '0';
                if (!lines[start]) {
                    ans.push_back(start.back());
                    lines[start] = true;
                    break;
                }
            }
        }
        return ans;
    }
};
