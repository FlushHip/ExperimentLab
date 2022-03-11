class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
    void dfs(Node *root, std::vector<int> &ans) {
        for (auto cld : root->children) {
            dfs(cld, ans);
        }
        ans.push_back(root->val);
    }
public:
    vector<int> postorder(Node* root) {
        std::vector<int> ans;
        if (root == nullptr) {
            return ans;
        }
        dfs(root, ans);
        return ans;
    }
};
