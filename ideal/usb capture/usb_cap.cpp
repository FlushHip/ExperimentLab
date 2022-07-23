#include "usb_cap.h"

#include <memory>

#include <spdlog/fmt/bin_to_hex.h>
#include <boost/algorithm/hex.hpp>

#include "logger.hpp"
#include "sample_bus.h"
#include "usb_cap/usb_cap.h"

namespace hestina {
namespace detail {

void usb_cap::start() {
    LOG_INFO << "start usb capture, filter : " << filter_;
    thread_ = std::make_unique<std::thread>([this] { main(); });
}

void usb_cap::main() const {
    Init();
    if (SetFilter(filter_) < 0) {
        LOG_ERROR << "set filter " << filter_ << " fail";
        return;
    }

    StartCapture(handle_capture);
    LOG_INFO << "end usb capture";
}

void usb_cap::handle_capture(char* data, int len) {
    sample_bus()(data, len);
}

}  // namespace detail
}  // namespace hestina
