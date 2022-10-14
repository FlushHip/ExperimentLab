#include "headers.h"

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        std::vector<int> used(arr.size(), 0);
        int ans = 0;
        for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
            used[arr[i]] = 1;
            ans += static_cast<int>(
                i + 1 == std::count(used.begin(), used.begin() + i + 1, 1));
        }
        return ans;
    }
};
