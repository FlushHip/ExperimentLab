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
    const int EN = 6;

    auto sol = std::make_unique<Solution>();

    std::pair<int, TreeNode *> root[EN]{
        { 8, new TreeNode(10
                , new TreeNode(5
                    , new TreeNode(3
                        , new TreeNode(3)
                        , new TreeNode(-2))
                    , new TreeNode(2
                        , nullptr
                        , new TreeNode(1)))
                , new TreeNode(-3
                    , nullptr
                    , new TreeNode(11))) },
        { 22, new TreeNode(5
                , new TreeNode(4
                    , new TreeNode(11
                        , new TreeNode(7)
                        , new TreeNode(2))
                    , nullptr)
                , new TreeNode(8
                    , new TreeNode(13)
                    , new TreeNode(4
                        , new TreeNode(5)
                        , new TreeNode(1)))) },
        { 5, new TreeNode(1
                , new TreeNode(2)
                , new TreeNode(3)) },
        { 0, new TreeNode(1
                , new TreeNode(2)
                , nullptr) },
        { 0, nullptr },
        { 1, new TreeNode(1
                , new TreeNode(2)
                , nullptr) },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->pathSum(root[L].second, root[L].first);

        std::cout << std::boolalpha << ans
            << std::endl << std::endl;
    }

    return 0;
}
