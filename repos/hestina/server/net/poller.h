#pragma once

#include <array>
#include <memory>
#include <vector>

#include <sys/epoll.h>

namespace hestina {
class channel;
class poller {
public:
    poller();
    ~poller();
    std::vector<channel*> poll();

    void update_channel(channel* channel);
    void remove_channel(channel* channel);

private:
    void update(int op, channel* channel);

    int fd_;
    enum { max_events_length = 1024 };
    std::array<epoll_event, max_events_length> events_{0};
};
}  // namespace hestina
