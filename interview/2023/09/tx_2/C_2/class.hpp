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
        long long h = tree_height(tree);
        return (mul(2, h) - 1 + kmod) % kmod;
    }

private:
    int tree_height(TreeNode* tree) {
        if (tree->left == nullptr && tree->right == nullptr) {
            return 1;
        }
        return 1 + std::max(tree_height(tree->left), tree_height(tree->right));
    }

    long long mul(long long x, long long y) {
        if (y == 0) {
            return 1;
        }
        auto half = mul(x, y / 2);
        return half * half % kmod * (y % 2 == 1 ? x : 1) % kmod;
    }

private:
    constexpr static long long kmod = 1e9 + 7;
};
