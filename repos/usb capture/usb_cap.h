#pragma once

#include "thread_controller.hpp"

namespace hestina {
namespace detail {

class usb_cap : public thread_controller {
public:
    usb_cap(int filter) : filter_(filter) {}

    void start() override;
    void stop() override;

private:
    void main() const;
    static void handle_capture(char* data, int len);

private:
    int filter_;
};

}  // namespace detail
}  // namespace hestina
