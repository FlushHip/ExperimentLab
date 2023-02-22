#include "headers.h"

class Foo {
public:
    Foo() {}

    void first(function<void()> printFirst) {
        printFirst();
        {
            std::lock_guard<std::mutex> lock(m_1_);
            ab_1_ = true;
        }
        cv_1_.notify_one();
    }

    void second(function<void()> printSecond) {
        {
            std::unique_lock<std::mutex> lock(m_1_);
            cv_1_.wait(lock, [this] { return ab_1_; });
        }
        printSecond();
        {
            std::lock_guard<std::mutex> lock(m_2_);
            ab_2_ = true;
        }
        cv_2_.notify_one();
    }

    void third(function<void()> printThird) {
        {
            std::unique_lock<std::mutex> lock(m_2_);
            cv_2_.wait(lock, [this] { return ab_2_; });
        }
        printThird();
    }

private:
    std::condition_variable cv_1_, cv_2_;
    std::mutex m_1_, m_2_;
    bool ab_1_{false}, ab_2_{false};
};
