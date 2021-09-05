class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        std::vector<std::vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }

        std::queue<Node*> qu;
        for (qu.emplace(root); !qu.empty(); ) {
            std::vector<int> res;
            for (int L = (int)qu.size(); L--; ) {
                auto now = qu.front();
                qu.pop();
                res.push_back(now->val);

                for (auto p : now->children) {
                    qu.push(p);
                }
            }
            ans.emplace_back(std::move(res));
        }

        return ans;
    }
};
