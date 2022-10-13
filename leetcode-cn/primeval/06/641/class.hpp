#include "headers.h"

class MyCircularDeque {
public:
    MyCircularDeque(int k) : que_(k + 1, 0) {}

    bool insertFront(int value) {
        if (isFull()) {
            return false;
        }
        front_ = (front_ - 1 + size_) % size_;
        que_[front_] = value;
        return true;
    }

    bool insertLast(int value) {
        if (isFull()) {
            return false;
        }
        que_[rear_] = value;
        rear_ = (rear_ + 1) % size_;
        return true;
    }

    bool deleteFront() {
        if (isEmpty()) {
            return false;
        }
        front_ = (front_ + 1) % size_;
        return true;
    }

    bool deleteLast() {
        if (isEmpty()) {
            return false;
        }
        rear_ = (rear_ - 1 + size_) % size_;
        return true;
    }

    int getFront() { return isEmpty() ? -1 : que_[front_]; }

    int getRear() { return isEmpty() ? -1 : que_[(rear_ - 1 + size_) % size_]; }

    bool isEmpty() const { return front_ == rear_; }

    bool isFull() const { return front_ == (rear_ + 1) % size_; }

private:
    std::vector<int> que_;
    int size_{static_cast<int>(que_.size())};
    int front_{0};
    int rear_{0};
};
