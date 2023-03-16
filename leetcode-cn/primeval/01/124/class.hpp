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
    int maxPathSum(TreeNode* root) {
        reset();

        dfs_1(root);
        int ans = -0x3f3f3f3f;
        dfs_2(root, ans);
        return ans;
    }

private:
    void dfs_2(TreeNode* root, int& ans) {
        if (root == nullptr) {
            return;
        }
        int sum = root->val;
        if (dp_[root].lhs - root->val > 0) {
            sum += dp_[root].lhs - root->val;
        }
        if (dp_[root].rhs - root->val > 0) {
            sum += dp_[root].rhs - root->val;
        }
        ans = std::max(ans, sum);
        dfs_2(root->left, ans);
        dfs_2(root->right, ans);
    }
    void dfs_1(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        dfs_1(root->left);
        dfs_1(root->right);
        int lhs_max = std::max(dp_[root->left].lhs, dp_[root->left].rhs);
        dp_[root].lhs = std::max(root->val, root->val + lhs_max);
        int rhs_max = std::max(dp_[root->right].lhs, dp_[root->right].rhs);
        dp_[root].rhs = std::max(root->val, root->val + rhs_max);
    }

    void reset() {
        dp_.clear();
        dp_[nullptr].lhs = dp_[nullptr].rhs = -0x3f3f3f3f;
    }

    struct sig_max {
        int lhs, rhs;
    };
    std::unordered_map<TreeNode*, sig_max> dp_;
};
