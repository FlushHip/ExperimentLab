#include "headers.h"

class FooBar {
private:
    int n_;
    bool f_{false};
    std::mutex con_mutex_;
    std::condition_variable con_var_;

public:
    FooBar(int n) : n_(n) {}

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n_; i++) {
            std::unique_lock<std::mutex> lock(con_mutex_);
            con_var_.wait(lock, [this] { return !f_; });
            printFoo();
            f_ = true;
            con_var_.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n_; i++) {
            std::unique_lock<std::mutex> lock(con_mutex_);
            con_var_.wait(lock, [this] { return f_; });
            printBar();
            f_ = false;
            con_var_.notify_all();
        }
    }
};
