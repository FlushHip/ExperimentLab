#include <iostream>
#include <memory>
#include <vector>

#include "class.hpp"

int main() {
    std::vector<std::pair<TreeNode*, std::vector<int>>> v{
        {new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(5)),
             new TreeNode(3, new TreeNode(6), new TreeNode(7))),
            {3, 4, 7, 5, 2, 2}},
    };
    for (auto&& [root, b] : v) {
        auto sol = std::make_unique<Solution>();
        std::vector<std::vector<int>> ans;
        for (auto* p : sol->solve(root, b)) {
            std::vector<int> line;
            for (; p != nullptr; p = p->next) {
                line.emplace_back(p->val);
            }
            ans.emplace_back(std::move(line));
        }
        dbg(ans);
    }
    return 0;
}
