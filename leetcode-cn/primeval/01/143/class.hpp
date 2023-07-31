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
    void reorderList(ListNode* head) {
        auto* ptr1 = head;
        auto* ptr2 = head;

        // split ptr1 & ptr2
        for (auto* ptr22 = ptr2;
             ptr22->next != nullptr && ptr22->next->next != nullptr;
             ptr2 = ptr2->next, ptr22 = ptr22->next->next) {
        }
        if (ptr1 == ptr2) {
            return;
        }

        auto* tptr = ptr2->next;
        ptr2->next = nullptr;
        ptr2 = tptr;

        // reverse ptr2
        auto root = std::make_unique<ListNode>();
        while (ptr2 != nullptr) {
            tptr = ptr2->next;
            ptr2->next = root->next;
            root->next = ptr2;
            ptr2 = tptr;
        }
        ptr2 = root->next;

        // cat ptr1 & ptr2
        int turn = 0;
        auto* p = root.get();
        for (; ptr2 != nullptr; turn = 1 - turn) {
            if (turn == 0) {
                p->next = ptr1;
                ptr1 = ptr1->next;
            } else {
                p->next = ptr2;
                ptr2 = ptr2->next;
            }
            p = p->next;
        }
        if (ptr1 != nullptr) {
            p->next = ptr1;
            p = p->next;
        }
        p->next = nullptr;
    }
};
