#include "headers.h"

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

    friend std::ostream& operator<<(std::ostream& os, const ListNode* ptr) {
        os << "[";
        for (; ptr != nullptr; ptr = ptr->next) {
            os << ptr->val;
            if (ptr->next != nullptr) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        return merge_list2(list1, list2);
    }

private:
    ListNode* merge_list2(ListNode* lhs, ListNode* rhs) {
        if (lhs == nullptr || rhs == nullptr) {
            return lhs == nullptr ? rhs : lhs;
        }
        ListNode *root = lhs->val < rhs->val ? lhs : rhs, *ptr = root;
        for (root == lhs ? (lhs = lhs->next) : (rhs = rhs->next);
             lhs != nullptr && rhs != nullptr; ptr = ptr->next) {
            if (lhs->val < rhs->val) {
                ptr->next = lhs;
                lhs = lhs->next;
            } else {
                ptr->next = rhs;
                rhs = rhs->next;
            }
        }
        if (lhs == nullptr) {
            ptr->next = rhs;
        } else {
            ptr->next = lhs;
        }
        return root;
    }
};
