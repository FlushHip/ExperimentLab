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
    void flatten(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        _flatten(root);
    }

private:
    TreeNode* _flatten(TreeNode* root) {
        if (root->left == nullptr && root->right == nullptr) {
            return root;
        }
        if (root->left == nullptr) {
            return _flatten(root->right);
        }
        if (root->right == nullptr) {
            auto* ret = _flatten(root->left);
            root->right = root->left;
            root->left = nullptr;
            return ret;
        }
        TreeNode* right = root->right;
        auto* next = _flatten(root->left);
        root->right = root->left;
        root->left = nullptr;
        next->right = right;
        next->left = nullptr;
        return _flatten(right);
    }
};
