struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        std::map<int, TreeNode *> node_map;
        std::map<TreeNode *, TreeNode *> parents;
        for (const auto &des : descriptions) {
            if (node_map.find(des[0]) == node_map.end()) {
                node_map[des[0]] = new TreeNode(des[0]);
            }
            if (node_map.find(des[1]) == node_map.end()) {
                node_map[des[1]] = new TreeNode(des[1]);
            }
            parents[node_map[des[1]]] = node_map[des[0]];
            if (des[2]) {
                node_map[des[0]]->left = node_map[des[1]];
            } else {
                node_map[des[0]]->right = node_map[des[1]];
            }
        }
        TreeNode *ans = nullptr;
        for (ans = node_map.begin()->second; parents.find(ans) != parents.end()
            ; ans = parents[ans]) {}
        return ans;
    }
};
