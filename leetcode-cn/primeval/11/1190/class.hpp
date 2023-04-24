#include "headers.h"

class Solution {
public:
    string reverseParentheses(string s) {
        unsigned int index = 0;
        return reverse(s, index);
    }

private:
    std::string reverse(std::string_view s, unsigned int& index) {
        std::string ret;
        while (index != s.size() && s[index] != ')') {
            for (auto& i = index; i < s.size() && std::isalpha(s[i]); ++i) {
                ret.push_back(s[i]);
            }
            if (index == s.size()) {
                return ret;
            }
            if (s[index] == '(') {
                ++index;
                auto sub = reverse(s, index);
                std::reverse(sub.begin(), sub.end());
                ret.append(sub);
                ++index;
            }
        }
        return ret;
    }
};
