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
    ListNode* reverseList(ListNode* head) {
        auto dummy = std::make_unique<ListNode>();
        while (head != nullptr) {
            auto last_next = dummy->next;
            auto last_h = head->next;
            dummy->next = head;
            head->next = last_next;
            head = last_h;
        }
        return dummy->next;
    }
};
