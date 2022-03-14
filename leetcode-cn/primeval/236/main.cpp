#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    TreeNode *p = nullptr, *q = nullptr;
    VList<std::tuple<TreeNode *, TreeNode *, TreeNode *>> v{
        { new TreeNode(6
            , p = new TreeNode(2
                , new TreeNode(0)
                , new TreeNode(4
                    , new TreeNode(3)
                    , new TreeNode(5)))
            , q = new TreeNode(8
                , new TreeNode(7)
                , new TreeNode(9))),
            p,
            q,
        },
        { new TreeNode(6
            , new TreeNode(2
                , p = new TreeNode(0)
                , q = new TreeNode(4
                    , new TreeNode(3)
                    , new TreeNode(5)))
            , new TreeNode(8
                , new TreeNode(7)
                , new TreeNode(9))),
            p,
            q,
        },
        { p = new TreeNode(6
            , new TreeNode(2
                , new TreeNode(0)
                , new TreeNode(4
                    , new TreeNode(3)
                    , new TreeNode(5)))
            , q = new TreeNode(8
                , new TreeNode(7)
                , new TreeNode(9))),
            p,
            q,
        },
        { p = new TreeNode(2
            , q = new TreeNode(1)),
            p,
            q,
        },
        { new TreeNode(3
            , p = new TreeNode(5
                , new TreeNode(6)
                , new TreeNode(2
                    , new TreeNode(7)
                    , new TreeNode(4)))
            , q = new TreeNode(1
                , new TreeNode(0)
                , new TreeNode(8))),
            p,
            q,
        },
        { new TreeNode(3
            , p = new TreeNode(5
                , new TreeNode(6)
                , new TreeNode(2
                    , new TreeNode(7)
                    , q = new TreeNode(4)))
            , new TreeNode(1
                , new TreeNode(0)
                , new TreeNode(8))),
            p,
            q,
        },
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto root = sol->lowestCommonAncestor(std::get<0>(v[L]), std::get<1>(v[L]), std::get<2>(v[L]));
        auto ans = root->val;

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
