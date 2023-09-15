#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

#include <dbg.h>

struct ListNode {
    int val;
    struct ListNode* next;
    ListNode(int x, ListNode* nx = nullptr) : val(x), next(nx) {}
};

class Solution {
public:
    ListNode* solve(std::vector<ListNode*>& a) {
        std::vector<int> arr;
        for (auto* p : a) {
            for (auto* q = p; q != nullptr; q = q->next) {
                arr.emplace_back(q->val);
            }
        }
        std::sort(arr.begin(), arr.end());
        auto aux = std::make_unique<ListNode>(0);
        auto* p = aux.get();
        for (auto v : arr) {
            p->next = new ListNode(v);
            p = p->next;
        }
        return aux->next;
    }
};
