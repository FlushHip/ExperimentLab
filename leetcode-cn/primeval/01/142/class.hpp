#include "headers.h"

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x, ListNode* n = nullptr) : val(x), next(n) {}
};

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }
        ListNode* last = nullptr;
        for (ListNode *p_1 = head->next, *p_2 = head->next->next;
             p_2 != nullptr; p_1 = p_1->next, p_2 = p_2->next->next) {
            if (p_1 == p_2) {
                last = p_1;
                break;
            }
            if (p_2->next == nullptr) {
                break;
            }
        }
        if (last == nullptr) {
            return nullptr;
        }
        ListNode* ans = head;
        for (ListNode* p = last; ans != p; ans = ans->next, p = p->next) {
        }
        return ans;
    }
};
