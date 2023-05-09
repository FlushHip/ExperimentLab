#include "headers.h"

#include "class.hpp"

std::ostream& operator<<(std::ostream& os, TreeNode* root) {
    std::function<std::vector<char>(TreeNode*)> print =
        [&](TreeNode* root) -> std::vector<char> {
        if (root->left == nullptr && root->right == nullptr) {
            return {static_cast<char>(root->val + '0')};
        }
        std::vector<char> ret;
        if (root->left) {
            auto left = print(root->left);
            ret.swap(left);
        } else {
            ret.push_back('-');
        }
        ret.push_back(root->val + '0');
        if (root->right) {
            auto right = print(root->right);
            ret.insert(ret.end(), right.begin(), right.end());
        } else {
            ret.push_back('-');
        }
        return ret;
    };
    os << print(root);
    return os;
}

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VList<> v{
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->generateTrees(v[L]);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            (std::chrono::steady_clock::now() - start_epoch) * 1000);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m" << std::boolalpha << ans
                  << std::endl
                  << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                  << duration.count() << "ms\x1b[0m" << std::endl
                  << std::endl;
    }

    return 0;
}
