class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        std::vector<int> ans;
        if (root == nullptr) {
            return ans;
        }

        std::queue<TreeNode*> qu;
        for (qu.emplace(root); !qu.empty(); ) {
            for (int L = (int)qu.size(); L--; ) {
                auto now = qu.front();
                qu.pop();
                if (!L) {
                    ans.push_back(now->val);
                }

                if (now->left != nullptr) {
                    qu.push(now->left);
                }
                if (now->right != nullptr) {
                    qu.push(now->right);
                }
            }
        }

        return ans;
    }
};
