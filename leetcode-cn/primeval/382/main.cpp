#include "headers.h"

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#include "class.hpp"

int main(int argc, char **argv)
{
    auto head = new ListNode(1
        , new ListNode(2
            , new ListNode(3)));

    auto sol = std::make_unique<Solution>(head);

    int maps[4] = { 0 };
    for (int i = 0; i < 100000; ++i) {
        ++maps[sol->getRandom()];
    }
    for (int i = 1; i <= 3; ++i) {
        std::cout << i << " : " << maps[i] << std::endl;
    }

    return 0;
}
