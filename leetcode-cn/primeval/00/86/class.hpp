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
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        auto lhs = std::make_unique<ListNode>(),
             rhs = std::make_unique<ListNode>();
        ListNode *p_l = lhs.get(), *p_r = rhs.get();
        for (auto* p = head; p != nullptr; p = p->next) {
            if (p->val < x) {
                p_l->next = p;
                p_l = p_l->next;
            } else {
                p_r->next = p;
                p_r = p_r->next;
            }
        }
        p_l->next = rhs->next;
        p_r->next = nullptr;
        return lhs->next;
    }
};
