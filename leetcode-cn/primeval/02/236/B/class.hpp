#include <functional>
#include <unordered_map>
#include <unordered_set>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x, TreeNode* left = nullptr, TreeNode* right = nullptr)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        std::unordered_map<TreeNode*, TreeNode*> ump;
        std::function<void(TreeNode*)> init_ump = [&](TreeNode* root) {
            if (root == nullptr) {
                return;
            }
            if (root->left != nullptr) {
                ump[root->left] = root;
                init_ump(root->left);
            }
            if (root->right != nullptr) {
                ump[root->right] = root;
                init_ump(root->right);
            }
        };
        ump[root] = nullptr;
        init_ump(root);

        std::unordered_set<TreeNode*> ust;
        for (auto* ptr = p; ptr != nullptr; ptr = ump[ptr]) {
            ust.emplace(ptr);
        }
        for (auto* ptr = q; ptr != nullptr; ptr = ump[ptr]) {
            if (ust.find(ptr) != ust.end()) {
                return ptr;
            }
        }
        return nullptr;
    }
};
