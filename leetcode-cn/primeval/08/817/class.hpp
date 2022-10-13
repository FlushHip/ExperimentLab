#include "headers.h"

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    int numComponents(ListNode* head, vector<int>& nums) {
        std::map<int, int> mp;
        int indexUp = 0, indexDown = 0;
        for (ListNode* p = head; p != nullptr; p = p->next) {
            mp[p->val] = indexUp++;
        }
        std::sort(nums.begin(), nums.end(),
            [&mp](const int lhs, const int rhs) { return mp[lhs] < mp[rhs]; });
        int ans = 0, sum = 0;
        indexUp = 0;
        for (ListNode* p = head;
             p != nullptr && indexDown < static_cast<int>(nums.size());
             p = p->next, ++indexUp) {
            if (indexUp == mp[nums[indexDown]]) {
                ++sum;
                ++indexDown;
            } else {
                ans += (sum != 0);
                sum = 0;
            }
        }
        return sum != 0 ? ++ans : ans;
    }
};
