class Solution {
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head)
        : head_(head)
        , gen_(std::random_device{}()) {
    }

    /** Returns a random node's value. */
    int getRandom() {
        int ans = head_->val, index = 2;
        for (auto p = head_->next; p != nullptr
            ; p = p->next, ++index) {
            int random_index =
                std::uniform_int_distribution<int>(1, index)(gen_);
            if (random_index == 1) {
                ans = p->val;
            }
        }

        return ans;
    }

private:
    const ListNode* head_;
    std::mt19937 gen_;
};
