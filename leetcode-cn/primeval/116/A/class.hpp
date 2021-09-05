class Solution {
public:
    Node* connect(Node* root) {
        if (root != nullptr) {
            dfs(root);
        }
        return root;
    }

    void dfs(Node *root) {
        if (root->left == nullptr) {
            return;
        }
        root->left->next = root->right;

        dfs(root->left);
        if (root->right != nullptr) {
            if (root->next != nullptr) {
                root->right->next = root->next->left;
            }
            dfs(root->right);
        }
    }
};
