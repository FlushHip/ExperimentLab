#include "headers.h"

class Solution {
public:
    string bestHand(vector<int>& ranks, vector<char>& suits) {
        if (std::all_of(suits.begin(), suits.end(),
                [value = suits.front()](char c) { return value == c; })) {
            return "Flush";
        }
        std::unordered_map<int, int> mp;
        for (int i : ranks) {
            ++mp[i];
        }

        bool has_2 = false;
        for (auto [_, cnt] : mp) {
            if (cnt >= 3) {
                return "Three of a Kind";
            }
            if (cnt == 2) {
                has_2 = true;
            }
        }
        return has_2 ? "Pair" : "High Card";
    }
};
