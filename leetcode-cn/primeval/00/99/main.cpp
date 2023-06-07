#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VList<TreeNode*> v{
        new TreeNode(4,
            new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr),
            nullptr),
        new TreeNode(1, new TreeNode(3, nullptr, new TreeNode(2)), nullptr),
        new TreeNode(
            3, new TreeNode(1), new TreeNode(4, new TreeNode(2), nullptr)),
    };

    auto print = [](TreeNode* root) {
        std::vector<int> ret;
        std::function<void(TreeNode*, std::vector<int>&)> dfs =
            [&dfs](TreeNode* root, std::vector<int>& ret) {
                if (root == nullptr) {
                    return;
                }
                dfs(root->left, ret);
                ret.push_back(root->val);
                dfs(root->right, ret);
            };
        dfs(root, ret);
        return ret;
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << print(v[L])
                  << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        sol->recoverTree(v[L]);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            (std::chrono::steady_clock::now() - start_epoch) * 1000);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m" << std::boolalpha
                  << print(v[L]) << std::endl
                  << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                  << duration.count() << "ms\x1b[0m" << std::endl
                  << std::endl;
    }

    return 0;
}
