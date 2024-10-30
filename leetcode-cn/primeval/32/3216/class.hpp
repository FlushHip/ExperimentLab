#include "headers.h"

class Solution {
public:
    string getSmallestString(string s) {
        std::priority_queue<std::string, std::vector<std::string>, std::greater<>> pri_que;
        int n = static_cast<int>(s.length());
        for (int i = 0; i < n - 1; i++) {
            if (s[i] % 2 == s[i + 1] % 2 && s[i] > s[i + 1]) {
                std::string ss(s);
                std::swap(ss[i], ss[i + 1]);
                pri_que.push(ss);
            }
        }
        return pri_que.empty() ? s : pri_que.top();
    }
};
