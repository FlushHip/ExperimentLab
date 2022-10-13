class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        ans_.clear();
        if (root == nullptr) {
            return ans_;
        }
        std::vector<int> path;
        dfs(root, 0, path, targetSum);
        return ans_;
    }

    void dfs(TreeNode* root, int sum, std::vector<int> &path ,int target) {
        struct DEFER {
            DEFER(std::vector<int> &path, int val) : path_(path), val_(val) {
                path_.push_back(val);
            }
            ~DEFER() {
                path_.pop_back();
            }

            std::vector<int> &path_;
            int val_;
        } defer(path, root->val);

        if (root->left == nullptr && root->right == nullptr) {
            if (sum + root->val == target) {
                ans_.emplace_back(path);
                return ;
            }
        }
        if (root->left != nullptr) {
            dfs(root->left, sum + root->val, path, target);
        }
        if (root->right != nullptr) {
            dfs(root->right, sum + root->val, path, target);
        }
    }

private:
    std::vector<std::vector<int>> ans_;
};
