#include "headers.h"

class ZeroEvenOdd {
private:
    int n_, i_{1};

    std::condition_variable cv_turn_;
    std::mutex m_turn_;
    int turn_{0};  // 0: 0, 1: odd, 2: even

public:
    ZeroEvenOdd(int n) : n_(n) {}

    void zero(function<void(int)> printNumber) {
        while (true) {
            std::unique_lock<std::mutex> lock(m_turn_);
            cv_turn_.wait(lock, [this] { return turn_ == 0 || i_ > n_; });
            if (i_ > n_) {
                break;
            }
            printNumber(0);
            turn_ = i_ % 2 == 1 ? 1 : 2;
            cv_turn_.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        while (true) {
            std::unique_lock<std::mutex> lock(m_turn_);
            cv_turn_.wait(lock, [this] { return turn_ == 2 || i_ > n_; });
            if (i_ > n_) {
                break;
            }
            printNumber(i_++);
            turn_ = 0;
            cv_turn_.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        while (true) {
            std::unique_lock<std::mutex> lock(m_turn_);
            cv_turn_.wait(lock, [this] { return turn_ == 1 || i_ > n_; });
            if (i_ > n_) {
                break;
            }
            printNumber(i_++);
            turn_ = 0;
            cv_turn_.notify_all();
        }
    }
};
