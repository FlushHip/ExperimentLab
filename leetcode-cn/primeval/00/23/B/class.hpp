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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return lists.empty() ? nullptr : merge_listk(lists);
    }

private:
    ListNode* merge_listk(std::vector<ListNode*>& lists) {
        for (int n = lists.size(); n != 1; n = (n + 1) / 2) {
            for (int i = 0, index = 0; i < n; i += 2) {
                if (i + 1 < n) {
                    lists[index++] = merge_list2(lists[i], lists[i + 1]);
                } else {
                    lists[index++] = lists[i];
                }
            }
        }
        return lists[0];
    }

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
