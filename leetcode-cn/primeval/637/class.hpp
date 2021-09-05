class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        std::vector<double> ans;
        if (root == nullptr) {
            return ans;
        }

        std::queue<TreeNode*> qu;
        for (qu.emplace(root); !qu.empty(); ) {
            double res = 0.0;
            int L = (int)qu.size();
            for (int i = 0; i < L; ++i) {
                auto now = qu.front();
                qu.pop();
                res += now->val;

                if (now->left != nullptr) {
                    qu.push(now->left);
                }
                if (now->right != nullptr) {
                    qu.push(now->right);
                }
            }

            ans.push_back(res / L);
        }

        return ans;
    }
};
