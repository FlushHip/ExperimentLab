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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, 0, preorder.size(), inorder, 0, inorder.size());
    }

private:
    TreeNode* build(const std::vector<int>& preorder,
        int pre_lhs,
        int pre_rhs,
        const std::vector<int>& inorder,
        int in_lhs,
        int in_rhs) {
        if (pre_rhs - pre_lhs > 0) {
            auto* root = new TreeNode(preorder[pre_lhs]);
            int lhs_len = std::find(inorder.begin() + in_lhs,
                              inorder.begin() + in_rhs, preorder[pre_lhs]) -
                inorder.begin() - in_lhs;
            root->left = build(preorder, pre_lhs + 1, pre_lhs + 1 + lhs_len,
                inorder, in_lhs, in_lhs + lhs_len);
            root->right = build(preorder, pre_lhs + 1 + lhs_len, pre_rhs,
                inorder, in_lhs + lhs_len + 1, in_rhs);
            return root;
        }
        return nullptr;
    }
};
