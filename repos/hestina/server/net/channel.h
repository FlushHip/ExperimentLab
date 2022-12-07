#pragma once

#include <cstdint>
#include <functional>

namespace hestina {

class event_loop;
class channel {
public:
    channel(event_loop* loop, int fd);
    ~channel();

    int fd() const;
    uint32_t listen_events() const;
    uint32_t ready_events() const;

    void enable_reading();
    void enable_writing();
    void disable_reading();
    void disable_writing();

    void enable_et();
    void disable_et();

    void handle_event();

    void remove();

    using event_callback_t = std::function<void()>;
    void set_any_event_callback(event_callback_t&& callback);
    void set_read_event_callback(event_callback_t&& callback);
    void set_write_event_callback(event_callback_t&& callback);
    void set_close_event_callback(event_callback_t&& callback);
    void set_error_event_callback(event_callback_t&& callback);

private:
    friend class poller;

    void update();

    event_loop* loop_;
    int fd_;
    bool is_add_{false};

    uint32_t listen_events_;
    uint32_t ready_events_{0};

    event_callback_t any_event_callback_{nullptr};
    event_callback_t read_event_callback_{nullptr};
    event_callback_t write_event_callback_{nullptr};
    event_callback_t close_event_callback_{nullptr};
    event_callback_t error_event_callback_{nullptr};
};

}  // namespace hestina
