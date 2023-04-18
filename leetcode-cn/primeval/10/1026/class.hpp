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
    int maxAncestorDiff(TreeNode* root) {
        int ans = 0;
        dfs(root, root->val, root->val, ans);
        return ans;
    }

private:
    void dfs(TreeNode* root, int min_value, int max_value, int& ans) {
        ans = std::max(ans,
            std::max(std::abs(root->val - min_value),
                std::abs(root->val - max_value)));
        min_value = std::min(min_value, root->val);
        max_value = std::max(max_value, root->val);
        if (root->left) {
            dfs(root->left, min_value, max_value, ans);
        }
        if (root->right) {
            dfs(root->right, min_value, max_value, ans);
        }
    }
};
