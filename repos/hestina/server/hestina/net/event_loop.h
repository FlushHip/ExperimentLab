#pragma once

#include <atomic>
#include <memory>

namespace hestina {

class poller;
class channel;

class event_loop {
public:
    event_loop();
    ~event_loop();

    void run();
    void stop();

    void update_channel(channel* channel);
    void remove_channel(channel* channel);

private:
    std::atomic_bool is_running_{false};
    std::unique_ptr<poller> poller_;
};

}  // namespace hestina
