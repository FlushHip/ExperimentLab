#include "headers.h"

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) { return dfs(root, k); }

private:
    int dfs(TreeNode* root, int& k) {
        if (root == nullptr) {
            return 0;
        }
        int ret = dfs(root->left, k);
        if (k == 0) {
            return ret;
        }
        if (--k == 0) {
            return root->val;
        }
        return dfs(root->right, k);
    }
};
