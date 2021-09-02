#include "headers.h"

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x, ListNode *p = nullptr) : val(x), next(p) {}
};

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 1;

    auto sol = std::make_unique<Solution>();

    std::pair<int, ListNode *> head[EN]{
        { 2, new ListNode(1
            , new ListNode(2
                , new ListNode(3
                    , new ListNode(4
                        , new ListNode(5))))) },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto p = sol->getKthFromEnd(head[L].second, head[L].first);

        for (auto q = p; q != nullptr; q = q->next) {
            std::cout << q->val << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
