#pragma once

#include <memory>
#include <thread>

namespace hestina {
namespace detail {

class thread_controller {
public:
    virtual ~thread_controller() noexcept {
        if (this->thread_ && this->thread_->joinable()) {
            this->thread_->join();
        }
    }
    virtual void start() = 0;
    virtual void stop() = 0;

protected:
    std::unique_ptr<std::thread> thread_{nullptr};
};

}  // namespace detail
}  // namespace hestina
