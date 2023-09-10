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
        auto* p = aux.get();
        while (p != nullptr && p->next != nullptr) {
            for (int x = p->val; p->next != nullptr && p->next->val == x;
                 p->next = p->next->next) {
            }
            p = p->next;
        }
        return aux->next;
    }
};
