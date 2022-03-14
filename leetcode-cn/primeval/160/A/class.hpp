struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x, ListNode *next = nullptr) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = 0, lenB = 0;
        for (auto p = headA; p != nullptr; p = p->next, ++lenA) {}
        for (auto p = headB; p != nullptr; p = p->next, ++lenB) {}
        if (lenA < lenB) {
            std::swap(lenA, lenB);
            std::swap(headA, headB);
        }

        for (int i = 0; i < lenA - lenB; ++i, headA = headA->next) {}

        for (; headA != nullptr && headA != headB; headA = headA->next, headB = headB->next) {}

        return headA;
    }
};
