#include "headers.h"

class Solution {
public:
    int takeCharacters(string s, int k) {
        if (k == 0) {
            return 0;
        }
        int n = static_cast<int>(s.size());
        std::array<int, 3> last{0, 0, 0};
        std::array<std::vector<int>, 3> count;
        count.fill(std::vector<int>(n, 0));
        count[s.front() - 'a'][0] = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 3; ++j) {
                count[j][i] = count[j][i - 1];
            }
            ++count[s[i] - 'a'][i];
        }
        int result = std::numeric_limits<int>::max();
        for (int top = n; top >= 0; --top) {
            std::array<int, 3> need{};
            for (int i = 0; i < 3; ++i) {
                need[i] = std::max(k - last[i], 0);
            }
            if (std::all_of(need.begin(), need.end(), [](int e) { return e == 0; })) {
                result = std::min(result, n - top);
                continue;
            }
            int max_value = 0;
            bool invalid = false;
            for (int i = 0; i < 3; ++i) {
                int lhs = std::lower_bound(count[i].begin(), count[i].begin() + top, need[i]) - count[i].begin();
                if (lhs == top) {
                    invalid = true;
                    break;
                }
                max_value = std::max(max_value, lhs + 1);
            }
            if (!invalid) {
                result = std::min(result, n - top + max_value);
            }

            if (top == 0) {
                continue;
            }
            ++last[s[top - 1] - 'a'];
        }
        return result == std::numeric_limits<int>::max() ? -1 : result;
    }
};
