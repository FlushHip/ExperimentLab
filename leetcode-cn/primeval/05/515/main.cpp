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
    const int EN = 5;

    auto sol = std::make_unique<Solution>();

    TreeNode *root[EN]{
        new TreeNode(1
            , new TreeNode(3
                , new TreeNode(5)
                , new TreeNode(3))
            , new TreeNode(2
                , nullptr
                , new TreeNode(9))),
        new TreeNode(1
            , new TreeNode(2)
            , new TreeNode(3)),
        new TreeNode(1),
        new TreeNode(1
            , nullptr
            , new TreeNode(2)),
        nullptr,
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->largestValues(root[L]);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
