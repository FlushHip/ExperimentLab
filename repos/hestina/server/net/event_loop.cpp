#include "event_loop.h"

#include "channel.h"
#include "poller.h"

#include <atomic>
#include <memory>
#include <thread>

namespace hestina {

event_loop::event_loop() : poller_(std::make_unique<poller>()) {}

event_loop::~event_loop() {
    stop();
}

void event_loop::run() {
    is_running_ = true;
    while (is_running_) {
        auto channels = poller_->poll();
        if (channels.empty()) {
            std::this_thread::yield();
            continue;
        }
        for (auto* channel : channels) {
            channel->handle_event();
        }
    }
}

void event_loop::stop() {
    is_running_ = false;
}

void event_loop::update_channel(channel* channel) {
    poller_->update_channel(channel);
}

void event_loop::remove_channel(channel* channel) {
    poller_->remove_channel(channel);
}

}  // namespace hestina
