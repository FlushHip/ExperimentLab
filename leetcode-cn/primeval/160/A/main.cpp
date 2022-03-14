#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    ListNode *common_root = nullptr;
    VList<std::pair<ListNode *, ListNode *>> v{
        {
            new ListNode(4
                , new ListNode(1
                    , common_root = new ListNode(8
                        , new ListNode(4
                            , new ListNode(5))))),
            new ListNode(5
                , new ListNode(6
                    , new ListNode(1
                        , common_root))),
        },
        {
            new ListNode(1
                , new ListNode(9
                    , new ListNode(1
                    , common_root = new ListNode(2
                        , new ListNode(4))))),
            new ListNode(3
                , common_root),
        },
        {
            new ListNode(2
                , new ListNode(6
                    , new ListNode(4))),
            new ListNode(1
                , new ListNode(5)),
        }
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto node = sol->getIntersectionNode(v[L].first, v[L].second);
        auto ans = node ? node-> val : 0;

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
