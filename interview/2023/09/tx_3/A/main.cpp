#include <iostream>
#include <memory>

#include "class.hpp"

int main() {
    std::vector<TreeNode*> v{
        new TreeNode(1, new TreeNode(0, new TreeNode(1), new TreeNode(0)),
            new TreeNode(0, nullptr, new TreeNode(1))),
    };
    for (auto* root : v) {
        auto sol = std::make_unique<Solution>();
        std::cout << sol->pathNumber(root) << std::endl;
    }
    return 0;
}
