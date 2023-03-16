#pragma once

#include <hestina/net/callback.h>
#include <hestina/timer/timer.h>

#include <atomic>
#include <memory>
#include <utility>

namespace hestina {

class channel;
class socket;
class event_loop;
class buffer;
class addr;
class timer_queue;

class connection : public std::enable_shared_from_this<connection> {
public:
    enum class status_t {
        connecting,
        connected,
        disconnecting,
        disconnected,
    };

    enum class peer_type_t {
        client,
        server,
    };

    connection(event_loop* loop,
        std::unique_ptr<socket>&& sock,
        peer_type_t type);
    ~connection();

    uint64_t id() const;
    status_t status() const;

    void send(std::string_view data);

    const addr& local_addr() const;
    const addr& peer_addr() const;

    void set_context(std::shared_ptr<void> ctx);
    template <typename T>
    std::shared_ptr<T> get_context();

    void close();

private:
    friend class tcp_server;
    friend class tcp_client;

    void established();
    void closed();
    void shutdown();

    void idle_timeout(size_t timeout, timer_queue* timer_que);
    void extend_life();

    void set_connection_establish_callback(
        const connection_establish_callback_t& callback);
    void set_data_arrive_callback(const data_arrive_callback_t& callback);
    void set_connection_close_callback(
        const connection_close_callback_t& callback);

    void do_read();
    void do_close();
    void do_error();

    void read_finished();

    uint64_t id_;
    peer_type_t peer_type_;

    std::unique_ptr<socket> socket_;
    std::unique_ptr<channel> channel_;

    std::unique_ptr<addr> local_addr_, peer_addr_;

    connection_establish_callback_t new_connection_callback_;
    data_arrive_callback_t data_arrive_callback_;
    connection_close_callback_t connection_close_callback_;

    std::unique_ptr<buffer> buffer_;

    status_t status_{status_t::connecting};

    static std::atomic_uint64_t sid_index;

    std::shared_ptr<void> context_;

    size_t idle_timeout_{0};
    timer_queue* idle_timer_{nullptr};
    timer_id last_timer_id_{timer::sinvalid_id};
    time_point last_timer_update_point_;
};

inline void connection::set_context(std::shared_ptr<void> ctx) {
    context_ = std::move(ctx);
}

template <typename T>
std::shared_ptr<T> connection::get_context() {
    return std::static_pointer_cast<T>(context_);
}

}  // namespace hestina
