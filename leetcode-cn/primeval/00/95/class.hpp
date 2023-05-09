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
    vector<TreeNode*> generateTrees(int n) { return generate(1, n); }

private:
    std::vector<TreeNode*> generate(int lhs, int rhs) {
        if (lhs > rhs) {
            return {nullptr};
        }
        std::vector<TreeNode*> ret;
        for (int root = lhs; root <= rhs; ++root) {
            auto left = generate(lhs, root - 1);
            auto right = generate(root + 1, rhs);
            for (auto* left_root : left) {
                for (auto* right_root : right) {
                    auto* mid_root = new TreeNode(root, left_root, right_root);
                    ret.push_back(mid_root);
                }
            }
        }
        return ret;
    }
};
