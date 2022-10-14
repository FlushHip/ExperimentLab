#include "headers.h"

class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        std::map<int, int> mp;
        for (const int num : nums1) {
            ++mp[num];
        }

        std::vector<int> ans;
        for (const int num : nums2) {
            if (auto iter = mp.lower_bound(num + 1); iter != mp.end()) {
                ans.push_back(iter->first);
                --iter->second;
                if (iter->second == 0) {
                    mp.erase(iter);
                }
            } else {
                ans.push_back(mp.begin()->first);
                --mp.begin()->second;
                if (mp.begin()->second == 0) {
                    mp.erase(mp.begin());
                }
            }
        }
        return ans;
    }
};
