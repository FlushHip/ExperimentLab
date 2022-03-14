struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x, TreeNode *left = nullptr, TreeNode *right = nullptr)
        : val(x), left(left), right(right) {}
};

class Solution {
    bool dfs(TreeNode *root, TreeNode *p, TreeNode *q, TreeNode* &ans) {
        if (root == nullptr || ans != nullptr) {
            return false;
        }
        bool lhs = dfs(root->left, p, q, ans), rhs = dfs(root->right, p, q, ans);
        if ((lhs && rhs) || ((root == p || root == q) && (lhs || rhs))) {
            ans = root;
        }
        return (lhs || rhs) || (root == p || root == q);
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode *ans = nullptr;
        dfs(root, p, q, ans);
        return ans;
    }
};
