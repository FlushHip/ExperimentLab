#include "headers.h"

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next = nullptr)
        : val(_val), left(_left), right(_right), next(_next) {}
};

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 4;

    auto sol = std::make_unique<Solution>();

    Node *root[EN]{
        new Node(1
            , new Node(2
                , new Node(4)
                , new Node(5))
            , new Node(3
                , new Node(6)
                , new Node(7))),
        new Node(1
            , new Node(2)
            , nullptr),
        nullptr,
        new Node(1),
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto head = sol->connect(root[L]);
        std::vector<std::vector<int>> ans;
        for (auto p = head; p != nullptr; p = p->left) {
            std::vector<int> res;
            for (auto q = p; q != nullptr; q = q->next) {
                res.push_back(q->val);
            }
            ans.emplace_back(std::move(res));
        }

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
