#include "headers.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 3;

    auto sol = std::make_unique<Solution>();

    TreeNode *root[EN]{
        new TreeNode(3
            , new TreeNode(9)
            , new TreeNode(20
                , new TreeNode(15)
                , new TreeNode(7))),
        nullptr,
        new TreeNode(10),
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->averageOfLevels(root[L]);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
