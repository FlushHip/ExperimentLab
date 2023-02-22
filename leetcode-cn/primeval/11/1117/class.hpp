#include "headers.h"

class H2O {
public:
    H2O() {}

    void hydrogen(function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lock(m_);
        cv_.wait(lock, [this] {
            return (h_ - 2 * o_ >= 0 && h_ - 2 * o_ < 2) || 2 * o_ - h_ == 2;
        });
        ++h_;
        releaseHydrogen();
        cv_.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        std::unique_lock<std::mutex> lock(m_);
        cv_.wait(lock, [this] { return h_ - 2 * o_ >= 0 && h_ - 2 * o_ <= 2; });
        ++o_;
        releaseOxygen();
        cv_.notify_all();
    }

private:
    int h_{0}, o_{0};
    std::condition_variable cv_;
    std::mutex m_;
};
