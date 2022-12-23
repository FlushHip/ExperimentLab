#pragma once

#include <atomic>
#include <memory>

namespace hestina {
namespace util {

template <typename T>
class mpsc_queue {
public:
    mpsc_queue()
        : head_(std::make_shared<node>())
        , tail_(head_.load(std::memory_order::relaxed)) {}

    ~mpsc_queue() = default;

    void push(T&& value);
    bool pop(T& value);
    bool empty() const;

private:
    struct node {
        node() = default;
        node(T&& d) : data(std::move(d)) {}

        T data;
        std::atomic<std::shared_ptr<node>> next{nullptr};
    };

    std::atomic<std::shared_ptr<node>> head_;
    std::atomic<std::shared_ptr<node>> tail_;
};

template <typename T>
void mpsc_queue<T>::push(T&& value) {
    auto nd = std::make_shared<node>(std::move(value));
    auto pre_head = head_.exchange(nd, std::memory_order::acq_rel);
    pre_head->next.store(nd, std::memory_order::release);
}

template <typename T>
bool mpsc_queue<T>::pop(T& value) {
    auto tail = tail_.load(std::memory_order::relaxed);
    auto next = tail->next.load(std::memory_order::acquire);

    if (next == nullptr) {
        return false;
    }
    value = std::move(next->data);
    tail_.store(next, std::memory_order::release);
    return true;
}

template <typename T>
bool mpsc_queue<T>::empty() const {
    auto tail = tail_.load(std::memory_order::relaxed);
    auto next = tail->next.load(std::memory_order::acquire);

    return next == nullptr;
}

}  // namespace util
}  // namespace hestina
