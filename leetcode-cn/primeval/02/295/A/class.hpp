#include "headers.h"

class MedianFinder {
public:
    MedianFinder() = default;

    void addNum(int num) {
        if (max_que_.size() == min_que_.size()) {
            if (min_que_.empty() || num <= min_que_.top()) {
                max_que_.emplace(num);
            } else {
                auto res = min_que_.top();
                min_que_.pop();
                max_que_.emplace(res);
                min_que_.emplace(num);
            }
        } else {
            if (num > max_que_.top()) {
                min_que_.emplace(num);
            } else {
                auto res = max_que_.top();
                max_que_.pop();
                min_que_.emplace(res);
                max_que_.emplace(num);
            }
        }
    }

    double findMedian() {
        if (max_que_.size() == min_que_.size()) {
            return (0.0 + max_que_.top() + min_que_.top()) / 2;
        }
        return max_que_.top();
    }

private:
    std::priority_queue<int, std::vector<int>, std::less<>> max_que_;
    std::priority_queue<int, std::vector<int>, std::greater<>> min_que_;
};
