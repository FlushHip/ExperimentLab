#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::vector<std::vector<int>>> v{
        {{20,15,1},{20,17,0},{50,20,1},{50,80,0},{80,19,1}},
        {{1,2,1},{2,3,0},{3,4,1}},
        {{39,70,1},{13,39,1},{85,74,1},{74,13,1},{38,82,1},{82,85,1}},
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto root = sol->createBinaryTree(v[L]);
        std::vector<int> ans;
        std::queue<TreeNode *> que({ root });
        while (!que.empty()) {
            auto node = que.front();
            que.pop();
            ans.push_back(node->val);
            if (node->left) {
                que.push(node->left);
            }
            if (node->right) {
                que.push(node->right);
            }
        }

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                            (std::chrono::steady_clock::now() - start_epoch);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m"
            << std::boolalpha << ans << std::endl
            << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                << duration.count() << "ms\x1b[0m"
            << std::endl << std::endl;
    }

    return 0;
}
