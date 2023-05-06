#include "headers.h"

class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        std::unordered_map<char, int> ump;
        int ans = 0;
        for (char c : croakOfFrogs) {
            if (c == 'c') {
                ++ump['c'];
                if (ump['k'] != 0) {
                    --ump['k'];
                } else {
                    ++ans;
                }
            } else if (c == 'r') {
                if (ump['c'] == 0) {
                    return -1;
                }
                --ump['c'];
                ++ump['r'];
            } else if (c == 'o') {
                if (ump['r'] == 0) {
                    return -1;
                }
                --ump['r'];
                ++ump['o'];
            } else if (c == 'a') {
                if (ump['o'] == 0) {
                    return -1;
                }
                --ump['o'];
                ++ump['a'];
            } else if (c == 'k') {
                if (ump['a'] == 0) {
                    return -1;
                }
                --ump['a'];
                ++ump['k'];
            }
        }
        ump['k'] = 0;
        return std::all_of(ump.begin(), ump.end(),
                   [](const auto& pr) { return pr.second == 0; })
            ? ans
            : -1;
    }
};
