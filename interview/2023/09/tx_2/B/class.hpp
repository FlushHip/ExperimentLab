#include <string>
#include <unordered_map>

#include <dbg.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    std::vector<TreeNode*> getBinaryTrees(std::vector<int>& preOrder,
        std::vector<int>& inOrder) {
        int n = static_cast<int>(preOrder.size());
        return build(0, n, preOrder, 0, n, inOrder);
    }

private:
    std::vector<TreeNode*> build(int pre_lhs,
        int pre_rhs,
        const std::vector<int>& preOrder,
        int in_lhs,
        int in_rhs,
        const std::vector<int>& inOrder) {
        if (pre_lhs == pre_rhs) {
            return {nullptr};
        }

        std::vector<TreeNode*> ret;
        int root_val = preOrder[pre_lhs];
        for (int i = in_lhs; i < in_rhs; ++i) {
            if (root_val == inOrder[i]) {
                int num_l = i - in_lhs;
                int num_r = in_rhs - i + 1;
                auto tree_lhs = build(pre_lhs + 1, pre_lhs + 1 + num_l,
                    preOrder, in_lhs, i, inOrder);
                auto tree_rhs = build(pre_lhs + 1 + num_l, pre_rhs, preOrder,
                    i + 1, in_rhs, inOrder);
                if (!tree_lhs.empty() && !tree_rhs.empty()) {
                    for (auto* lhs : tree_lhs) {
                        for (auto* rhs : tree_rhs) {
                            auto* root = new TreeNode(root_val);
                            root->left = lhs;
                            root->right = rhs;
                            ret.emplace_back(root);
                        }
                    }
                }
            }
        }
        return ret;
    }
};
