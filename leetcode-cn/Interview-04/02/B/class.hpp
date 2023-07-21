#include "headers.h"

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 0) {
            return nullptr;
        }
        std::queue<std::pair<TreeNode*, std::pair<int, int>>> que;
        auto* root = new TreeNode(0);
        que.push({root, {0, n}});
        while (!que.empty()) {
            auto [p, interval] = que.front();
            que.pop();
            int mid = (interval.first + interval.second) / 2;
            p->val = nums[mid];
            if (interval.first != mid) {
                p->left = new TreeNode(0);
                que.push({p->left, {interval.first, mid}});
            } else {
                p->left = nullptr;
            }
            if (mid + 1 != interval.second) {
                p->right = new TreeNode(0);
                que.push({p->right, {mid + 1, interval.second}});
            } else {
                p->right = nullptr;
            }
        }
        return root;
    }
};
