class Solution {
public:
    int rob(TreeNode* root) {
        return dfs(root);
    }

    int dfs(const TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        if (dp.end() != dp.find(root)) {
            return dp[root];
        }

        int ans1 = dfs(root->left) + dfs(root->right);
        int ans2 = root->val;
        if (root->left) {
            ans2 += dfs(root->left->left) + dfs(root->left->right);
        }
        if (root->right) {
            ans2 += dfs(root->right->left) + dfs(root->right->right);
        }

        return dp[root] = std::max(ans1, ans2);
    }
private:
    std::map<const TreeNode*, int> dp;
};
