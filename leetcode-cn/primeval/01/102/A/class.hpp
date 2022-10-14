class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> ans;
        std::queue<std::pair<unsigned int, TreeNode*>> qu;

        for (qu.emplace(0u, root); !qu.empty(); ) {
            auto now = qu.front();
            qu.pop();
            if (now.second == nullptr) {
                continue;
            }
            if (now.first + 1 > ans.size()) {
                ans.emplace_back();
            }
            ans[now.first].push_back(now.second->val);

            qu.emplace(now.first + 1, now.second->left);
            qu.emplace(now.first + 1, now.second->right);
        }

        return ans;
    }
};
