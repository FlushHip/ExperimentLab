class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        std::vector<int> ans;
        if (root == nullptr) {
            return ans;
        }

        std::queue<TreeNode*> qu;
        for (qu.emplace(root); !qu.empty(); ) {
            int res = std::numeric_limits<int>::min();
            for (int L = (int)qu.size(); L--; ) {
                auto now = qu.front();
                qu.pop();
                res = std::max(res, now->val);

                if (now->left != nullptr) {
                    qu.push(now->left);
                }
                if (now->right != nullptr) {
                    qu.push(now->right);
                }
            }

            ans.push_back(res);
        }

        return ans;
    }
};
