class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        return root == nullptr ? false : dfs(root, 0, targetSum);
    }

    bool dfs(TreeNode* root, int sum, int target) {
        if (root->left == nullptr && root->right == nullptr) {
            return sum + root->val == target;
        }
        if (root->left != nullptr && dfs(root->left, sum + root->val, target)) {
            return true;
        }
        return root->right != nullptr && dfs(root->right, sum + root->val, target);
    }
};
