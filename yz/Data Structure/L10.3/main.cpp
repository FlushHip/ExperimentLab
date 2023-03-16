#include <iostream>
#include <memory>

int main(int argc, char **argv)
{
    struct node {
        int value;
        std::unique_ptr<node> lhs, rhs;
    };
    for (int n; std::cin >> n; ) {
        std::unique_ptr<node> tree;
        for (int L = 0; L < n; ++L) {
            int value = 0, pre = -1;
            std::cin >> value;
            for (auto *root = &tree; ; ) {
                if (!(*root)) {
                    *root = std::make_unique<node>();
                    (*root)->value = value;
                    break;
                }
                pre = (*root)->value;
                if ((*root)->value > value)
                    root = &(*root)->lhs;
                else
                    root = &(*root)->rhs;

            }
            std::cout << pre << std::endl;
        }
    }
    return 0;
}