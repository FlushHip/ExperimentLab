#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VList<TreeNode*> v{
        new TreeNode(4,
            new TreeNode(
                1, new TreeNode(0), new TreeNode(2, nullptr, new TreeNode(3))),
            new TreeNode(
                6, new TreeNode(5), new TreeNode(7, nullptr, new TreeNode(8)))),
        new TreeNode(0, nullptr, new TreeNode(1)),
        new TreeNode(1, new TreeNode(0), new TreeNode(2)),
        new TreeNode(
            3, new TreeNode(2, new TreeNode(1), nullptr), new TreeNode(4)),
    };

    auto print = [](TreeNode* root) {
        /*
        std::stack<TreeNode*> st{{root}};
        std::vector<int> ret;
        auto* p = root;
        while (p != nullptr || !st.empty()) {
            if (p != nullptr) {
                ret.push_back(p->val);
                st.push(p);
                p = p->left;
            } else {
                p = st.top();
                st.pop();
                p = p->right;
            }
        }
        */
        std::vector<int> ret;
        std::queue<TreeNode*> que{{root}};
        while (!que.empty()) {
            auto* p = que.front();
            que.pop();
            ret.push_back(p->val);
            if (p->left != nullptr) {
                que.push(p->left);
            }
            if (p->right != nullptr) {
                que.push(p->right);
            }
        }
        return ret;
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << print(v[L])
                  << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = print(sol->convertBST(v[L]));

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
