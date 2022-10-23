#include "headers.h"

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        std::string ans;
        auto it_a = word1.begin(), it_b = word2.begin();
        for (; it_a != word1.end() && it_b != word2.end(); ++it_a, ++it_b) {
            ans.push_back(*it_a);
            ans.push_back(*it_b);
        }
        if (it_a != word1.end()) {
            ans.append(it_a, word1.end());
        }
        if (it_b != word2.end()) {
            ans.append(it_b, word2.end());
        }
        return ans;
    }
};
