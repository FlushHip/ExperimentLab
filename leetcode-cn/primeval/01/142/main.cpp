#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    ListNode *in = nullptr, *root = nullptr, *last = nullptr;
    VList<ListNode*> v{
        (root = new ListNode(
             3, in = new ListNode(2, new ListNode(0, last = new ListNode(4)))),
            last->next = in, root),
        (root = in = new ListNode(1, last = new ListNode(2)), last->next = in,
            root),
        new ListNode(1),
        nullptr,
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto node = sol->detectCycle(v[L]);
        auto ans = node == nullptr ? 0xffff : node->val;

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
