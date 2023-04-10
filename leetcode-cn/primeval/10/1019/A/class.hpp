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
    vector<int> nextLargerNodes(ListNode* head) {
        std::vector<int> ans;
        std::unordered_map<ListNode*, ListNode*> ump;
        recursion(head, ump, ans, 0);
        return ans;
    }

private:
    void recursion(ListNode* head,
        std::unordered_map<ListNode*, ListNode*>& ump,
        std::vector<int>& ans,
        int index) {
        if (head == nullptr) {
            ans.resize(index);
            return;
        }
        recursion(head->next, ump, ans, index + 1);
        for (auto* p = head->next; p != nullptr; p = ump[p]) {
            if (head->val < p->val) {
                ans[index] = p->val;
                ump[head] = p;
                return;
            }
        }
        ump[head] = nullptr;
        ans[index] = 0;
    }
};
