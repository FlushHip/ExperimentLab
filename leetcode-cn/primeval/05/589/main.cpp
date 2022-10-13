#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<Node *> v{
        new Node(1, {
            new Node(3, {
                new Node(5),
                new Node(6) }),
            new Node(2),
            new Node(4) }),
        new Node(1, {
            new Node(2),
            new Node(3, {
                new Node(6),
                new Node(7, {
                    new Node(11, {
                        new Node(14) }) }) }),
            new Node(4, {
                new Node(8, {
                    new Node(12) }) }),
            new Node(5, {
                new Node(9, {
                    new Node(13) }),
                new Node(10) }) }),
            nullptr,
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :" << std::endl;

        std::cout << "\t\x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto ans = sol->preorder(v[L]);

        std::cout << "\t\x1b[31mans -> \x1b[0m" << ans
            << std::endl << std::endl;
    }

    return 0;
}
