#include <iostream>
#include <memory>

struct node
{
    int value;
    std::unique_ptr<node> lhs, rhs;
};

void print_pre(const std::unique_ptr<node> &root)
{
    if (!root)
        return;
    std::cout << root->value << " ";
    print_pre(root->lhs);
    print_pre(root->rhs);
}

void print_mid(const std::unique_ptr<node> &root)
{
    if (!root)
        return;
    print_mid(root->lhs);
    std::cout << root->value << " ";
    print_mid(root->rhs);
}

void print_last(const std::unique_ptr<node> &root)
{
    if (!root)
        return;
    print_last(root->lhs);
    print_last(root->rhs);
    std::cout << root->value << " ";
}

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::unique_ptr<node> tree;
        for (int L = 0; L < n; ++L) {
            int value = 0;
            std::cin >> value;
            for (auto *root = &tree; ; ) {
                if (!(*root)) {
                    *root = std::make_unique<node>();
                    (*root)->value = value;
                    break;
                }
                if ((*root)->value == value)
                    break;
                if ((*root)->value > value)
                    root = &(*root)->lhs;
                else
                    root = &(*root)->rhs;
            }
        }
        print_pre(tree);
        std::cout << std::endl;
        print_mid(tree);
        std::cout << std::endl;
        print_last(tree);
        std::cout << std::endl;
    }
    return 0;
}