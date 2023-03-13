#include "headers.h"

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    int kthLargest(TreeNode* root, int k) { return dfs(root, k); }

private:
    int dfs(TreeNode* root, int& cnt) {
        if (root->right) {
            int ret = dfs(root->right, cnt);
            if (cnt <= 0) {
                return ret;
            }
        }
        if (--cnt == 0) {
            return root->val;
        }
        if (root->left) {
            return dfs(root->left, cnt);
        }
        return 0;
    }
};
