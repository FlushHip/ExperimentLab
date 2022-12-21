#include "headers.h"

class StockSpanner {
public:
    int next(int price) {
        arr_.push_back(price);
        while (!st_.empty() && arr_[st_.top()] <= price) {
            st_.pop();
        }
        int ans = st_.empty() ? index_ + 1 : index_ - st_.top();
        st_.push(index_++);
        return ans;
    }

private:
    int index_{0};
    std::vector<int> arr_;
    std::stack<int> st_;
};
