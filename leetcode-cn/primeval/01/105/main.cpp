#include <functional>
#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VTList<std::vector<int>, std::vector<int>> v{
        {
            {3, 9, 20, 15, 7},
            {9, 3, 15, 20, 7},
        },
        {
            {-1},
            {-1},
        },
    };

    std::function<void(TreeNode*)> print = [&print](TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        std::cout << root->val << std::endl;
        print(root->left);
        print(root->right);
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->buildTree(UNPACK_2(v[L]));
        print(ans);

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
