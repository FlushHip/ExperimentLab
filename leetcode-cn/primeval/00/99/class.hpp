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
    void recoverTree(TreeNode* root) {
        TreeNode *x = nullptr, *y = nullptr;
        for (TreeNode* last = nullptr; root != nullptr;) {
            if (root->left != nullptr) {
                auto* left_r = root->left;
                while (left_r->right != nullptr && left_r->right != root) {
                    left_r = left_r->right;
                }
                if (left_r->right == nullptr) {
                    left_r->right = root;
                    root = root->left;
                } else {
                    left_r->right = nullptr;

                    if (last != nullptr && root->val < last->val) {
                        y = root;
                        if (x == nullptr) {
                            x = last;
                        } else {
                            // break;
                        }
                    }
                    // visit(root);
                    last = root;
                    root = root->right;
                }
            } else {
                if (last != nullptr && root->val < last->val) {
                    y = root;
                    if (x == nullptr) {
                        x = last;
                    } else {
                        // break;
                    }
                }
                // visit(root);
                last = root;
                root = root->right;
            }
        }
        std::swap(x->val, y->val);
    }
};
