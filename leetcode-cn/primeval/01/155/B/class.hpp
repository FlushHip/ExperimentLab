#include "headers.h"

class MinStack {
public:
    MinStack() {}

    void push(int val) {
        if (ctx_.empty()) {
            ctx_.emplace(0);
            min_value_ = val;
        } else {
            ctx_.emplace(val - min_value_);
            min_value_ = std::min(0LL + val, min_value_);
        }
    }

    void pop() {
        if (ctx_.top() < 0) {
            min_value_ = min_value_ - ctx_.top();
        }
        ctx_.pop();
    }

    int top() { return ctx_.top() < 0 ? min_value_ : min_value_ + ctx_.top(); }

    int getMin() { return min_value_; }

private:
    long long min_value_{0};
    std::stack<long long> ctx_;
};
