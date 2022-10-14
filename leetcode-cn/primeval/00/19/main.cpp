#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VList<std::pair<ListNode*, int>> v{
        {new ListNode(1,
             new ListNode(
                 2, new ListNode(3, new ListNode(4, new ListNode(5))))),
            1},
        {new ListNode(1,
             new ListNode(
                 2, new ListNode(3, new ListNode(4, new ListNode(5))))),
            2},
        {new ListNode(1,
             new ListNode(
                 2, new ListNode(3, new ListNode(4, new ListNode(5))))),
            3},
        {new ListNode(1,
             new ListNode(
                 2, new ListNode(3, new ListNode(4, new ListNode(5))))),
            4},
        {new ListNode(1,
             new ListNode(
                 2, new ListNode(3, new ListNode(4, new ListNode(5))))),
            5},
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto root = sol->removeNthFromEnd(v[L].first, v[L].second);

        std::vector<int> ans;
        for (auto p = root; p != nullptr; p = p->next) {
            ans.push_back(p->val);
        }

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
