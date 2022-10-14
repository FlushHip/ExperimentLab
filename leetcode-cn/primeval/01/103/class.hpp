class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        std::vector<std::vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }

        std::queue<TreeNode*> qu;
        for (qu.emplace(root); !qu.empty(); ) {
            std::vector<int> res;
            for (int L = (int)qu.size(); L--; ) {
                auto now = qu.front();
                qu.pop();
                res.push_back(now->val);

                if (now->left != nullptr) {
                    qu.push(now->left);
                }
                if (now->right != nullptr) {
                    qu.push(now->right);
                }
            }
            ans.emplace_back(std::move(res));
        }

        for (int i = 1; i < (int)ans.size(); i += 2) {
            std::reverse(ans[i].begin(), ans[i].end());
        }

        return ans;
    }
};
