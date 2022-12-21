#include "headers.h"

class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        return std::accumulate(word1.begin(), word1.end(), ""s) ==
            std::accumulate(word2.begin(), word2.end(), ""s);
    }
};
