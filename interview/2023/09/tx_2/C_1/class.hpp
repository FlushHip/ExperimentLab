#include <unordered_map>

#include <dbg.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int x, TreeNode* lhs = nullptr, TreeNode* rhs = nullptr)
        : val(x), left(lhs), right(rhs) {}
};

class Solution {
public:
    int getTreeSum(TreeNode* tree) {
        subtree_height(tree);
        return dfs(tree);
    }

private:
    int subtree_height(TreeNode* tree) {
        if (tree->left == nullptr && tree->right == nullptr) {
            return cnt_[tree] = 1;
        }
        return cnt_[tree] = 1 +
            std::max(subtree_height(tree->left), subtree_height(tree->right));
    }

    int dfs(TreeNode* tree) {
        if (tree->left == nullptr && tree->right == nullptr) {
            return 1;
        }
        auto lhs = dfs(tree->left);
        auto rhs = dfs(tree->right);
        return (1 + 2 * (cnt_[tree->left] > cnt_[tree->right] ? lhs : rhs)) %
            kmod;
    }

private:
    std::unordered_map<TreeNode*, int> cnt_;
    constexpr static long long kmod = 1e9 + 7;
};
