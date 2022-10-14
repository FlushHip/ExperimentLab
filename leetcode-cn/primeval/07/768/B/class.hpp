#include "headers.h"

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        std::vector<int> sorted(arr);
        std::sort(sorted.begin(), sorted.end());
        std::unordered_map<int, int> mp;
        int ans = 0;
        for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
            ++mp[arr[i]];
            if (!mp[arr[i]]) {
                mp.erase(arr[i]);
            }
            --mp[sorted[i]];
            if (!mp[sorted[i]]) {
                mp.erase(sorted[i]);
            }
            ans += mp.empty();
        }
        return ans;
    }
};
