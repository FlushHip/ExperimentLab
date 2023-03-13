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
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        auto [mid, pre] = find_mid(head);
        pre->next = nullptr;

        auto* lhs = sortList(head);
        auto* rhs = sortList(mid);

        return merge(lhs, rhs);
    }

private:
    std::pair<ListNode*, ListNode*> find_mid(ListNode* head) {
        ListNode* tail = head;
        ListNode *mid = head, *pre = head;
        while (tail != nullptr && tail->next != nullptr) {
            pre = mid;
            mid = mid->next;
            tail = tail->next->next;
        }
        return {mid, pre};
    }

    ListNode* merge(ListNode* lhs, ListNode* rhs) {
        if (lhs == nullptr) {
            return rhs;
        }
        if (rhs == nullptr) {
            return lhs;
        }
        ListNode* ret = nullptr;
        if (lhs->val < rhs->val) {
            ret = lhs;
            lhs = lhs->next;
        } else {
            ret = rhs;
            rhs = rhs->next;
        }
        ListNode* p = ret;
        for (; lhs != nullptr && rhs != nullptr; p = p->next) {
            if (lhs->val < rhs->val) {
                p->next = lhs;
                lhs = lhs->next;
            } else {
                p->next = rhs;
                rhs = rhs->next;
            }
        }
        if (lhs != nullptr) {
            p->next = lhs;
        }
        if (rhs != nullptr) {
            p->next = rhs;
        }
        return ret;
    }
};
