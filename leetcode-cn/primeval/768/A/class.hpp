#include "headers.h"

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        std::vector<int> sorted(arr);
        std::sort(sorted.begin(), sorted.end());
        std::vector<int> used(arr.size(), 0);
        int ans = 0;
        for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
            int index = std::lower_bound(sorted.begin(), sorted.end(), arr[i]) -
                sorted.begin();
            for (; used[index]; ++index) {
            }
            used[index] = 1;
            ans += static_cast<int>(i + 1 ==
                std::accumulate(used.begin(), used.begin() + i + 1, 0));
        }
        return ans;
    }
};
