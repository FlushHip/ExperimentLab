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
    ListNode* reverseKGroup(ListNode* head, int k) {
        auto* next_list = head;
        int cnt = 0;
        for (; cnt < k && next_list != nullptr; ++cnt) {
            next_list = next_list->next;
        }
        if (cnt < k) {
            return head;
        }
        auto* ret = head;
        auto* p = head->next;
        for (int i = 0; i < k - 1; ++i) {
            auto* next = p->next;
            p->next = ret;
            ret = p;
            p = next;
        }
        head->next = reverseKGroup(next_list, k);

        return ret;
    }
};
