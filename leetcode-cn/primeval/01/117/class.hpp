class Solution {
public:
    Node* connect(Node* root) {
        if (root != nullptr) {
            dfs(root);
        }
        return root;
    }

    void dfs(Node *root) {
        if (root->right != nullptr) {
            for (auto p = root->next; p != nullptr
                ; p = p->next) {
                if (p->left != nullptr) {
                    root->right->next = p->left;
                    break;
                }
                if (p->right != nullptr) {
                    root->right->next = p->right;
                    break;
                }
            }
            dfs(root->right);
        }
        if (root->left != nullptr) {
            if (root->right != nullptr) {
                root->left->next = root->right;
            } else {
                for (auto p = root->next; p != nullptr
                    ; p = p->next) {
                    if (p->left != nullptr) {
                        root->left->next = p->left;
                        break;
                    }
                    if (p->right != nullptr) {
                        root->left->next = p->right;
                        break;
                    }
                }
            }
            dfs(root->left);
        }
    }
};
