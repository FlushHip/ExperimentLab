#include "headers.h"

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return recur(nums, 0, static_cast<int>(nums.size()));
    }

private:
    TreeNode* recur(const std::vector<int>& nums, int lhs, int rhs) {
        if (lhs == rhs) {
            return nullptr;
        }
        int mid = (lhs + rhs) / 2;
        auto* root = new TreeNode(nums[mid]);
        root->left = recur(nums, lhs, mid);
        root->right = recur(nums, mid + 1, rhs);
        return root;
    }
};
