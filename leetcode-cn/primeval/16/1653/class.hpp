#include "headers.h"

class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();
        std::vector<int> cnt_a(n);
        cnt_a[0] = s[0] == 'a';
        for (int i = 1; i < n; ++i) {
            cnt_a[i] = cnt_a[i - 1] + (s[i] == 'a');
        }
        int ans = n;
        for (int i = -1; i < n; ++i) {
            ans = std::min(ans,
                i + 1 - (i >= 0 ? cnt_a[i] : 0) + cnt_a[n - 1] -
                    (i + 1 == n ? cnt_a[n - 1] : cnt_a[i + 1]));
        }
        return ans;
    }
};
