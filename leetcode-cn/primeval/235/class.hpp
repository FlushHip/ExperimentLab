struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x, TreeNode *left = nullptr, TreeNode *right = nullptr)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode *ans = root;
        for ( ; !((ans->val >= p->val && ans->val < q->val)
                    || (ans->val > p->val && ans->val <= q->val)
                    || (ans->val >= q->val && ans->val < p->val)
                    || (ans->val > q->val && ans->val <= p->val)); ) {
            if (ans->val > p->val && ans->val > q->val) {
                ans = ans->left;
            }
            if (ans->val < p->val && ans->val < q->val) {
                ans = ans->right;
            }
        }
        return ans;
    }
};
