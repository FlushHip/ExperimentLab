#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VTList<ListNode*, int> v{
        {new ListNode(1,
             new ListNode(4,
                 new ListNode(
                     3, new ListNode(2, new ListNode(5, new ListNode(2)))))),
            3},
        {new ListNode(2, new ListNode(1)), 2},
    };

    auto print = [](ListNode* head) {
        std::vector<int> ret;
        for (auto* p = head; p != nullptr; p = p->next) {
            ret.emplace_back(p->val);
        }
        return ret;
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << print(std::get<0>(v[L]))
                  << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto* ans = sol->partition(UNPACK_2(v[L]));

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            (std::chrono::steady_clock::now() - start_epoch) * 1000);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m" << std::boolalpha
                  << print(ans) << std::endl
                  << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                  << duration.count() << "ms\x1b[0m" << std::endl
                  << std::endl;
    }

    return 0;
}
