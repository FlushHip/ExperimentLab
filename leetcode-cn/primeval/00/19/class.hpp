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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto root = std::make_unique<ListNode>(0, head);
        auto p = head, q = head, pre = root.get();
        for (--n; n-- > 0; p = p->next) {
        }
        for (; p->next != nullptr; p = p->next) {
            q = q->next;
            pre = pre->next;
        }
        pre->next = q->next;
        return root->next;
    }
};
