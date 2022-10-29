#include "headers.h"

class Solution {
public:
    int countMatches(vector<vector<string>>& items,
        string ruleKey,
        string ruleValue) {
        return std::count_if(items.begin(), items.end(), [&](const auto& item) {
            return (ruleKey[0] == 't' && ruleValue == item[0]) ||
                (ruleKey[0] == 'c' && ruleValue == item[1]) ||
                (ruleKey[0] == 'n' && ruleValue == item[2]);
        });
    }
};
