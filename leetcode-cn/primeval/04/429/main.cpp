#include "headers.h"

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 4;

    auto sol = std::make_unique<Solution>();

    Node *root[EN]{
        new Node(1, {
            new Node(3, {
                new Node(5),
                new Node(6),
            }),
            new Node(2),
            new Node(4),
        }),
        new Node(1, {
            new Node(2),
            new Node(3, {
                new Node(6),
                new Node(7, {
                    new Node(11, {
                        new Node(14),
                    }),
                }),
            }),
            new Node(4, {
                new Node(8, {
                    new Node(12),
                }),
            }),
            new Node(5, {
                new Node(9, {
                    new Node(13),
                }),
                new Node(10),
            }),
        }),
        nullptr,
        new Node(1),
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->levelOrder(root[L]);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
