#include "headers.h"

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        std::unordered_set<int> ust;
        for (int num : nums) {
            ust.insert(num);
        }
        return nums.size() != ust.size();
    }
};
