#include <string>
#include <unordered_map>

#include <dbg.h>

class Solution {
public:
    int minOperations(std::string str) {
        std::unordered_map<char, int> ump;
        for (char c : str) {
            ++ump[c];
        }
        int res = 26 - static_cast<int>(ump.size());
        int ret = 0;
        dbg(ump, res);
        for (auto&& [_, cnt] : ump) {
            while (res > 0 && cnt > 2) {
                cnt -= 2;
                --res;
                ++ret;
            }
            ret += cnt - 1;
        }
        return ret;
    }
};
