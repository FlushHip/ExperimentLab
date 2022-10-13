#include "headers.h"

class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k > 1) {
            std::sort(s.begin(), s.end());
            return s;
        }
        int size = static_cast<int>(s.size());
        std::string result = s;
        s += s;
        for (int i = 0; i < size; ++i) {
            if (auto str = s.substr(i, size); result > str) {
                result = std::move(str);
            }
        }
        return result;
    }
};
