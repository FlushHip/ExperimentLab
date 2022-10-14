#include "headers.h"

class MyCircularQueue {
public:
    MyCircularQueue(int k) : que_(k + 1, 0) {}

    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        que_[rear_] = value;
        rear_ = (rear_ + 1) % size_;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        front_ = (front_ + 1) % size_;
        return true;
    }

    int Front() { return isEmpty() ? -1 : que_[front_]; }

    int Rear() { return isEmpty() ? -1 : que_[(rear_ - 1 + size_) % size_]; }

    bool isEmpty() const { return front_ == rear_; }

    bool isFull() const { return front_ == (rear_ + 1) % size_; }

private:
    std::vector<int> que_;
    int size_{static_cast<int>(que_.size())};
    int front_{0};
    int rear_{0};
};
