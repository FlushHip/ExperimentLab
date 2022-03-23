#include <iostream>
#include <memory>

struct node
{
    int value;
    std::unique_ptr<node> lhs, rhs;
};

std::unique_ptr<node> build_tree(const std::string &str)
{
    std::unique_ptr<node> tree;
    for (const auto value : str) {
        for (auto *root = &tree; ; ) {
            if (!(*root)) {
                *root = std::make_unique<node>();
                (*root)->value = value - '0';
                break;
            }
            if ((*root)->value > value - '0')
                root = &(*root)->lhs;
            else
                root = &(*root)->rhs;
        }
    }
    return tree;
}

bool is_same_tree(const std::unique_ptr<node> &a, std::unique_ptr<node> b)
{
    if (!a && !b)
        return true;
    if ((a && !b) || (!a && b))
        return false;
    return a->value == b->value && is_same_tree(a->lhs, std::move(b->lhs)) && is_same_tree(a->rhs, std::move(b->rhs));
}

int main(int argc, char **argv)
{
    for (int n; std::cin >> n && n; ) {
        std::string str;
        std::cin >> str;
        auto root = build_tree(str);
        for (int i = 0; i < n; ++i) {
            std::cin >> str;
            std::cout << (is_same_tree(root, build_tree(str)) ? "YES" : "NO") << std::endl;
        }
    }
    return 0;
}