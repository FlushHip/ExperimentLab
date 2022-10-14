struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x, ListNode *next = nullptr) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        auto pA = headA, pB = headB;
        for ( ; pA != pB; ) {
            pA = pA ? pA->next : headA;
            pB = pB ? pB->next : headB;
        }
        return pA;
    }
};
