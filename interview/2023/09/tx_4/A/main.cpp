#include <iostream>
#include <memory>

#include "class.hpp"

int main() {
    std::vector<std::vector<ListNode*>> v{
        {
            new ListNode(1, new ListNode(3, new ListNode(5))),
            new ListNode(2, new ListNode(4, new ListNode(6))),
            new ListNode(1,
                new ListNode(2,
                    new ListNode(
                        3, new ListNode(4, new ListNode(5, new ListNode(6)))))),
        },
    };
    for (auto root : v) {
        auto sol = std::make_unique<Solution>();
        std::cout << sol->solve(root) << std::endl;
    }
    return 0;
}
