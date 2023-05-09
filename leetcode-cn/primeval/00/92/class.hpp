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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        auto aux = std::make_unique<ListNode>(0, head);
        auto* p = aux.get();
        for (int i = 0; i < left - 1; ++i) {
            p = p->next;
        }
        auto* q = p->next;
        auto* last = q;
        for (int i = 0; i < right - left + 1; ++i) {
            auto* q_next = q->next;
            q->next = p->next;
            p->next = q;
            q = q_next;
        }
        last->next = q;
        return aux->next;
    }
};
