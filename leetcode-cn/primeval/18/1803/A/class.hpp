#include "headers.h"

class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        return fn(nums, high) - fn(nums, low - 1);
    }

private:
    enum { max_bit_length = 16 };
    struct tree {
        int cnt_{0};
        std::array<std::unique_ptr<tree>, 2> child_{{nullptr, nullptr}};
    };

    int fn(const std::vector<int>& nums, int top) {
        int ans = 0;
        tree root;
        add(root, nums[0]);
        std::bitset<max_bit_length> top_bits(top);
        for (int i = 1; i < nums.size(); ++i) {
            std::bitset<max_bit_length> numsi_bits(nums[i]);
            ans += get(root, numsi_bits, top_bits);
            add(root, numsi_bits);
        }
        return ans;
    }

    void add(tree& root, const std::bitset<max_bit_length>& top) {
        tree* p = &root;
        for (int i = max_bit_length - 1; i >= 0; --i) {
            if (p->child_[top[i]] == nullptr) {
                p->child_[top[i]] = std::make_unique<tree>();
            }
            p = p->child_[top[i]].get();
            ++p->cnt_;
        }
    }

    int get(const tree& root,
        const std::bitset<max_bit_length>& x,
        const std::bitset<max_bit_length>& top) {
        int result = 0;
        const tree* p = &root;
        for (int i = max_bit_length - 1; i >= 0 && p != nullptr; --i) {
            if (top[i] == 0) {
                p = p->child_[x[i]].get();
            } else {
                result +=
                    p->child_[x[i]] == nullptr ? 0 : p->child_[x[i]]->cnt_;
                p = p->child_[x[i] ^ 1U].get();
            }
        }
        return result + (p != nullptr ? p->cnt_ : 0);
    }
};
