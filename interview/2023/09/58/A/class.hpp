#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

#include <dbg.h>

class Solution {
public:
    int calculate(int m, int n, std::vector<int>& scores) {
        int size = static_cast<int>(scores.size());
        std::sort(scores.begin(), scores.end());
        int ans = -1;
        for (int i = 0; i < size - 1; ++i) {
            if (scores[i] != scores[i + 1]) {
                if (m <= i + 1 && i + 1 <= n && m <= size - i - 1 &&
                    size - i - 1 <= n) {
                    ans = scores[i];
                    break;
                }
            }
        }
        return ans;
    }
};
