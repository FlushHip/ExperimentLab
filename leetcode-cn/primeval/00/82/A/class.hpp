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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        auto aux =
            std::make_unique<ListNode>(std::numeric_limits<int>::min(), head);
        auto *pre = aux.get(), *p = aux.get(), *q = head;
        for (; q != nullptr; q = q->next) {
            if (p->val != q->val && p->next != q) {
                pre->next = q;
                p = q;
            } else if (p->val != q->val && p->next == q) {
                pre = p;
                p = q;
            }
        }
        if (p != nullptr && p->next != nullptr && p->val == p->next->val) {
            pre->next = nullptr;
        }
        return aux->next;
    }
};
