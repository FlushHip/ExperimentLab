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
        struct context {
            int index;
            int value;
        };
        std::stack<context> st;
        int idx = 0;
        for (auto* p = head; p != nullptr; p = p->next, ++idx) {
            ans.push_back({});
            while (!st.empty() && st.top().value < p->val) {
                auto [index, value] = st.top();
                st.pop();
                ans[index] = p->val;
            }
            st.push(context{idx, p->val});
        }
        return ans;
    }
};
