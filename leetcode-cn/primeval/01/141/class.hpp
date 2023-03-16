#include "headers.h"

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x, ListNode* n = nullptr) : val(x), next(n) {}
};

class Solution {
public:
    bool hasCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        for (ListNode *p_1 = head->next, *p_2 = head->next->next;
             p_2 != nullptr; p_1 = p_1->next, p_2 = p_2->next->next) {
            if (p_1 == p_2) {
                return true;
            }
            if (p_2->next == nullptr) {
                break;
            }
        }
        return false;
    }
};
