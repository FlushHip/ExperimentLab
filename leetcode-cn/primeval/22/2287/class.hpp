#include "headers.h"

class Solution {
public:
    int rearrangeCharacters(string s, string target) {
        std::unordered_map<char, int> map_s, map_t;
        for (char c : s) {
            ++map_s[c];
        }
        for (char c : target) {
            ++map_t[c];
        }

        int ans = s.size();
        for (auto [c, cnt] : map_t) {
            if (map_s[c] < cnt) {
                return 0;
            }
            ans = std::min(ans, map_s[c] / cnt);
        }
        return ans;
    }
};
