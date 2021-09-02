class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        auto pre = head, ret = pre;
        for (int i = 0; i < k - 1 && pre != nullptr; ++i, pre = pre->next);
        if (pre == nullptr)
            return nullptr;
        for (; pre->next != nullptr; ret = ret->next, pre = pre->next);
        return ret;
    }
};
