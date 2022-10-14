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
    Solution sol{};
    TreeNode A(3
        , new TreeNode(2
            , nullptr
            , new TreeNode(3))
        , new TreeNode(3
            , nullptr
            ,  new TreeNode(1))
    );

    TreeNode B(3
        , new TreeNode(4
            , new TreeNode(1)
            , new TreeNode(3))
        , new TreeNode(5
            , nullptr
            ,  new TreeNode(1))
    );

    std::cout << sol.rob(&A) << std::endl;
    std::cout << sol.rob(&B) << std::endl;
    return 0;
}
