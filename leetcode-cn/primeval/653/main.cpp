#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    TreeNode *root = nullptr;
    VList<std::pair<TreeNode *, int>> v{
        { root = new TreeNode(5
            , new TreeNode(3
                , new TreeNode(2)
                , new TreeNode(4))
            , new TreeNode(6
                , nullptr
                , new TreeNode(7))),
            9,
        },
        {
            root,
            28,
        },
        {
            new TreeNode(1),
            2,
        }

    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->findTarget(v[L].first, v[L].second);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                            (std::chrono::steady_clock::now() - start_epoch);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m"
            << std::boolalpha << ans << std::endl
            << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                << duration.count() << "ms\x1b[0m"
            << std::endl << std::endl;
    }

    return 0;
}
