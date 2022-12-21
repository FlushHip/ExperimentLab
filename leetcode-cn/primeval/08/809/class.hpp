#include "headers.h"

class Solution {
public:
    int expressiveWords(string s, vector<string>& words) {
        auto fn = [](std::string_view s, std::string_view word) {
            int s_lhs = 0, w_lhs = 0;
            int s_rhs = 0, w_rhs = 0;
            for (; s_lhs < s.size() && w_lhs < word.size();) {
                if (s[s_lhs] != word[w_lhs]) {
                    return false;
                }
                for (s_rhs = s_lhs; s_rhs < s.size() && s[s_lhs] == s[s_rhs];
                     ++s_rhs) {
                }
                for (w_rhs = w_lhs;
                     w_rhs < word.size() && word[w_lhs] == word[w_rhs];
                     ++w_rhs) {
                }
                if (!((s_rhs - s_lhs > w_rhs - w_lhs && s_rhs - s_lhs >= 3) ||
                        (s_rhs - s_lhs == w_rhs - w_lhs))) {
                    return false;
                }
                s_lhs = s_rhs;
                w_lhs = w_rhs;
            }
            return s_lhs == s.size() && w_lhs == word.size();
        };
        return std::count_if(words.begin(), words.end(),
            [&](std::string_view word) { return fn(s, word); });
    }
};
