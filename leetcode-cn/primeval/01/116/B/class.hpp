class Solution {
public:
    Node* connect(Node* root) {
        if (root != nullptr) {
            for (auto head = root->next, pre = root; head != nullptr
                ; head = head->next) {
                // TODO : 非递归做法
            }
        }
        return root;
    }
};
