#include "headers.h"

class MedianFinder {
public:
    MedianFinder() = default;

    void addNum(int num) {
        int n = static_cast<int>(mul_st_.size());
        mul_st_.emplace(num);
        if (n == 0) {
            lhs_ = rhs_ = mul_st_.begin();
        } else if (n % 2 == 0) {
            if (num < *lhs_) {
                --rhs_;
            } else if (num >= *rhs_) {
                ++lhs_;
            } else {
                ++lhs_;
                --rhs_;
            }
        } else {
            if (num >= *lhs_) {
                ++rhs_;
            } else {
                --lhs_;
            }
        }
    }

    double findMedian() { return (0.0 + *lhs_ + *rhs_) / 2; }

private:
    std::multiset<int> mul_st_;
    std::multiset<int>::iterator lhs_, rhs_;
};
