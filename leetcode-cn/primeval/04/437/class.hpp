class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return 0;
        }
        std::map<int, int> mp{ { 0, 1 } };
        ans_ = 0;
        dfs(root, 0, mp, targetSum);
        return ans_;
    }

    void dfs(TreeNode* root, int pre, std::map<int, int> &mp, int target) {
        pre += root->val;
        if (mp.count(pre - target)) {
            ans_ += mp[pre - target];
        }
        struct DEFER {
            DEFER(std::map<int, int> &mp, int pre) : mp_(mp), pre_(pre) {
                ++mp_[pre_];
            }
            ~DEFER() {
                --mp_[pre_];
            }

            std::map<int, int> &mp_;
            int pre_;
        } defer(mp, pre);

        if (root->left == nullptr && root->right == nullptr) {
            return ;
        }
        if (root->left != nullptr) {
            dfs(root->left, pre, mp, target);
        }
        if (root->right != nullptr) {
            dfs(root->right, pre, mp, target);
        }
    }

private:
    int ans_;
};
