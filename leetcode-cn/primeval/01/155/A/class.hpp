#include "headers.h"

class MinStack {
public:
    MinStack() {}

    void push(int val) {
        if (ctx_.empty()) {
            ctx_.emplace(ctx{val, val});
        } else {
            ctx_.emplace(ctx{val, std::min(ctx_.top().min, val)});
        }
    }

    void pop() { ctx_.pop(); }

    int top() { return ctx_.top().value; }

    int getMin() { return ctx_.top().min; }

private:
    struct ctx {
        int value;
        int min;
    };
    std::stack<ctx> ctx_;
};
