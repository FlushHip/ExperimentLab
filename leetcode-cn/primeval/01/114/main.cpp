#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VList<TreeNode*> v{
        new TreeNode(1, new TreeNode(2, new TreeNode(3), new TreeNode(4)),
            new TreeNode(5, nullptr, new TreeNode(6))),
        nullptr,
        new TreeNode(0),
    };

    auto print = [](TreeNode* root) {
        std::vector<int> ret;
        while (root != nullptr) {
            ret.push_back(root->val);
            root = root->right;
        }
        return ret;
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        sol->flatten(v[L]);
        auto ans = print(v[L]);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            (std::chrono::steady_clock::now() - start_epoch) * 1000);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m" << std::boolalpha << ans
                  << std::endl
                  << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                  << duration.count() << "ms\x1b[0m" << std::endl
                  << std::endl;
    }

    return 0;
}
