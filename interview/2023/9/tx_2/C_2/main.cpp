#include <iostream>
#include <memory>

#include "class.hpp"

int main() {
    std::vector<TreeNode*> v{
        new TreeNode(0, new TreeNode(0), new TreeNode(0)),
        new TreeNode(0, new TreeNode(0, new TreeNode(0), new TreeNode(0)),
            new TreeNode(0)),
    };
    for (auto* root : v) {
        auto sol = std::make_unique<Solution>();
        std::cout << sol->getTreeSum(root) << std::endl;
    }
    return 0;
}
