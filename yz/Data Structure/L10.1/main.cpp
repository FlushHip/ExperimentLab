#include <iostream>
#include <string>
#include <memory>

struct Node {
    char c;
    std::unique_ptr<Node> lhs, rhs;
};

void build(std::unique_ptr<Node> &root, const std::string &str, std::size_t &index)
{
    if (index == str.size())
        return;
    auto c = str[index++];
    if (c == '#') {
        root = nullptr;
    } else {
        root = std::make_unique<Node>();
        root->c = c;
        build(root->lhs, str, index);
        build(root->rhs, str, index);
    }
}

void print(const std::unique_ptr<Node> &root)
{
    if (!root)
        return;
    print(root->lhs);
    std::cout << root->c << " ";
    print(root->rhs);
}

int main(int argc, char **argv)
{
    for (std::string str; std::cin >> str; ) {
        std::unique_ptr<Node> root;
        std::size_t aux_index = 0;
        build(root, str, aux_index);
        print(root);
        std::cout << std::endl;
    }
    return 0;
}