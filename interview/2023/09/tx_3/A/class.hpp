#include <string>
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
    int pathNumber(TreeNode* root) {
        int sum_0 = 0, sum_1 = 0;
        int ans = 0;
        dfs(root, sum_0, sum_1, ans);
        return ans;
    }

private:
    void dfs(TreeNode* root, int sum_0, int sum_1, int& ans) {
        if (root->left == nullptr && root->right == nullptr) {
            if (root->val == 0) {
                ++sum_0;
            } else {
                ++sum_1;
            }
            if (sum_1 == sum_0 + 1) {
                ++ans;
            }
            return;
        }
        if (root->val == 0) {
            if (root->left) {
                dfs(root->left, sum_0 + 1, sum_1, ans);
            }
            if (root->right) {
                dfs(root->right, sum_0 + 1, sum_1, ans);
            }
        } else {
            if (root->left) {
                dfs(root->left, sum_0, sum_1 + 1, ans);
            }
            if (root->right) {
                dfs(root->right, sum_0, sum_1 + 1, ans);
            }
        }
    }
};
