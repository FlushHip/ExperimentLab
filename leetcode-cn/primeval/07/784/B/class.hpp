#include "headers.h"

class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        int cnt = std::count_if(
            s.begin(), s.end(), [](char c) { return isalpha(c); });
        std::vector<std::string> ans;
        for (long long mask = 0; mask < (1ll << cnt); ++mask) {
            std::string str;
            for (int i = 0, k = 0; i < s.size(); ++i) {
                if (std::isalpha(s[i])) {
                    if (mask & (1ll << k++)) {
                        str.push_back(std::toupper(s[i]));
                    } else {
                        str.push_back(std::tolower(s[i]));
                    }
                } else {
                    str.push_back(s[i]);
                }
            }
            ans.emplace_back(std::move(str));
        }
        return ans;
    }
};
