#include <algorithm>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <dbg.h>

struct ListNode {
    int val;
    struct ListNode* next;
    ListNode(int x, ListNode* nx = nullptr) : val(x), next(nx) {}
};

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int x, TreeNode* lhs = nullptr, TreeNode* rhs = nullptr)
        : val(x), left(lhs), right(rhs) {}
};

class Solution {
public:
    std::vector<ListNode*> solve(TreeNode* root, std::vector<int>& b) {
        std::unordered_map<int, int> ump;
        init(root, ump);
        int root_val = root->val;
        ump[root_val] = -1;
        int m = static_cast<int>(b.size());
        std::vector<ListNode*> ans;
        for (int pre_val = root_val, i = 0; i < m; ++i) {
            if (pre_val == b[i]) {
                ans.emplace_back(new ListNode(b[i]));
                continue;
            }
            std::unordered_map<int, bool> used;
            for (auto p = pre_val; p != root_val; p = ump[p]) {
                used[p] = true;
            }
            auto top = root_val;
            for (auto p = b[i]; p != root_val; p = ump[p]) {
                if (used[p]) {
                    top = p;
                }
            }

            auto* aux = new ListNode(pre_val);
            auto* q = aux;
            for (auto p = ump[pre_val]; p != -1 && p != top; p = ump[p]) {
                q->next = new ListNode(p);
                q = q->next;
            }
            if (pre_val != top) {
                q->next = new ListNode(top);
                q = q->next;
            }
            std::vector<int> line;
            for (auto p = b[i]; p != top; p = ump[p]) {
                line.emplace_back(p);
            }
            std::reverse(line.begin(), line.end());
            for (auto p : line) {
                q->next = new ListNode(p);
                q = q->next;
            }
            q->next = nullptr;

            ans.emplace_back(aux);

            pre_val = b[i];
        }
        return ans;
    }

private:
    void init(TreeNode* root, std::unordered_map<int, int>& ump) {
        if (root != nullptr) {
            if (root->left) {
                ump[root->left->val] = root->val;
                init(root->left, ump);
            }
            if (root->right) {
                ump[root->right->val] = root->val;
                init(root->right, ump);
            }
        }
    }
};
