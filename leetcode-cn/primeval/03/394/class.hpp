#include "headers.h"

class Solution {
public:
    string decodeString(string s) {
        unsigned int idx = 0;
        return deal_str(s, idx);
    }

private:
    std::string deal_str(std::string_view s, unsigned int& idx) {
        std::string ans;
        while (idx < s.size()) {
            for (; idx < s.size() && std::isalpha(s[idx]); ++idx) {
                ans.push_back(s[idx]);
            }
            if (idx == s.size() || s[idx] == ']') {
                break;
            }
            ans += deal_digit(s, idx);
        }
        return ans;
    }

    std::string deal_digit(std::string_view s, unsigned int& idx) {
        std::string digit;
        for (; std::isdigit(s[idx]); ++idx) {
            digit.push_back(s[idx]);
        }
        int repeat = std::stoi(digit);
        ++idx;
        auto str = deal_str(s, idx);
        ++idx;
        std::string ans;
        for (int i = 0; i < repeat; ++i) {
            ans.append(str);
        }
        return ans;
    }
};
