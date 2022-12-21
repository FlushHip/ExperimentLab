#include "headers.h"

class Solution {
public:
    int magicalString(int n) { return ans_array()[n - 1]; }

private:
    enum { max_length = 100000 };
    static const std::array<int, max_length>& ans_array() {
        static auto ans = [] {
            std::array<int, max_length> line;
            std::array<int, max_length> ans;
            line[0] = 1;
            line[1] = 2;
            ans[0] = ans[1] = 1;
            for (int i = 1, j = 1, pre = 1; i < max_length; ++i) {
                int now = ((pre - 1) ^ 1) + 1;
                for (int k = 0; k < line[i] && j < max_length; ++k, ++j) {
                    line[j] = now;
                    ans[j] = ans[j - 1] + (now == 1);
                }
                pre = now;
                if (!(j < max_length)) {
                    break;
                }
            }
            return ans;
        }();
        return ans;
    }
};
