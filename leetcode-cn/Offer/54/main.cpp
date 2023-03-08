#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    TreeNode* root = nullptr;
    VTList<TreeNode*, int> v{
        {new TreeNode(
             3, new TreeNode(1, nullptr, new TreeNode(2)), new TreeNode(4)),
            1},
        {root = new TreeNode(5,
             new TreeNode(
                 3, new TreeNode(2, new TreeNode(1), nullptr), new TreeNode(4)),
             new TreeNode(6)),
            3},
        {root, 4},
        {root, 5},
        {root, 6},
        {root, 1},
        {root, 2},
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->kthLargest(UNPACK_2(v[L]));

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
