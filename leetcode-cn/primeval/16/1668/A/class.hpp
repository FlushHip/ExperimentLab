#include "headers.h"

class Solution {
public:
    int maxRepeating(string sequence, string word) {
        int n = sequence.size(), m = word.size();
        int ans = 0;
        std::string word_repeat;
        for (int k = 1; k * m <= n; ++k) {
            word_repeat.append(word);
            if (sequence.find(word_repeat) != std::string::npos) {
                ans = k;
            }
        }
        return ans;
    }
};
