struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    bool dfs(const TreeNode *root, const TreeNode *ops, int target) {
        if (root == nullptr) {
            return false;
        }
        if (root != ops && root->val == target) {
            return true;
        }
        return root->val > target ? dfs(root->left, ops, target) : dfs(root->right, ops, target);
    }
public:
    bool findTarget(TreeNode* root, int k) {
        std::stack<TreeNode *> st({ root });
        for (auto p = root; !st.empty(); ) {
            if (p) {
                st.push(p);
                p = p->left;
            } else if (!st.empty()){
                p = st.top();
                st.pop();

                if (dfs(root, p, k - p->val)) {
                    return true;
                }

                p = p->right;
            }
        }
        return false;
    }
};
