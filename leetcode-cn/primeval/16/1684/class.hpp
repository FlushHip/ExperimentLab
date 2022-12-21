#include "headers.h"

class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        unsigned int root_mark = mark(allowed);
        return std::count_if(
            words.begin(), words.end(), [root_mark](const std::string& word) {
                return root_mark == (root_mark | mark(word));
            });
    }

private:
    static unsigned int mark(std::string_view str) {
        unsigned int ans = 0U;
        for (char c : str) {
            ans |= 1U << (c - 'a');
        }
        return ans;
    }
};
