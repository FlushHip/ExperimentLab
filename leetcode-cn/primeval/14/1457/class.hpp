#include "headers.h"

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    int pseudoPalindromicPaths(TreeNode* root) {
        std::array<int, 10> cnt_val{};
        int ret = 0;
        std::function<void(TreeNode*)> fn = [&](TreeNode* root) {
            /*
            struct raii_t {
                raii_t(std::function<void()>&& c, std::function<void()>&& d)
                    : d_{d} {
                    c();
                }
                ~raii_t() { d_(); }

            private:
                std::function<void()> d_;
            };
            raii_t raii(
                [&] { ++cnt_val[root->val]; }, [&] { --cnt_val[root->val]; });
            */
            ++cnt_val[root->val];
            std::unique_ptr<void, std::function<void(void*)>> raii(
                &raii, [&](void*) { --cnt_val[root->val]; });
            if (root->left == nullptr && root->right == nullptr) {
                ret += std::accumulate(cnt_val.begin() + 1, cnt_val.end(), 0,
                           [](auto ret, auto value) {
                               return ret + (value & 1);
                           }) <= 1;
                return;
            }
            if (root->left) {
                fn(root->left);
            }
            if (root->right) {
                fn(root->right);
            }
        };
        fn(root);
        return ret;
    }
};
