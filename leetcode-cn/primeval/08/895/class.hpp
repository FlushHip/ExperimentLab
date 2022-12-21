#include <unordered_map>
#include "headers.h"

class FreqStack {
public:
    void push(int val) {
        int freq = ++freq_[val];
        if (freq - 1 == line_.size()) {
            line_.emplace_back();
        }
        line_[freq - 1].push(val);
    }

    int pop() {
        int ret = line_.back().top();
        line_.back().pop();
        --freq_[ret];
        if (line_.back().empty()) {
            line_.pop_back();
        }
        return ret;
    }

private:
    std::unordered_map<int, int> freq_;
    std::vector<std::stack<int>> line_;
};
