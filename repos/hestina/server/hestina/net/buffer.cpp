#include "buffer.h"

#include <hestina/util/funs.h>

#include <algorithm>
#include <cassert>

#include <netinet/in.h>
#include <sys/uio.h>

namespace hestina {

buffer::buffer(size_t length) : data_(length, 0) {}

void buffer::append(std::string_view data) {
    ensure_writeable_bytes(data.length());
    std::copy(data.begin(), data.end(), begin() + tail_);
    tail_ += data.length();
}

std::string_view buffer::data() {
    return data_;
}

void buffer::clear() {
    data_.clear();
}

char* buffer::begin() {
    return data_.data();
}

const char* buffer::begin() const {
    return data_.data();
}

size_t buffer::readable_bytes() const {
    return tail_ - head_;
}

size_t buffer::writeable_bytes() const {
    return data_.size() - tail_;
}

std::string_view buffer::peek() const {
    return peek(readable_bytes());
}

std::string_view buffer::peek(size_t n) const {
    assert(readable_bytes() >= n);
    return {begin() + head_, n};
}

uint8_t buffer::peek_int8() const {
    return *static_cast<uint16_t*>(
        reinterpret_cast<void*>(const_cast<char*>(peek(1).data())));
}

uint16_t buffer::peek_int16() const {
    return ntohs(*static_cast<uint16_t*>(
        reinterpret_cast<void*>(const_cast<char*>(peek(2).data()))));
}

uint32_t buffer::peek_int32() const {
    return ntohl(*static_cast<uint32_t*>(
        reinterpret_cast<void*>(const_cast<char*>(peek(4).data()))));
}

uint64_t buffer::peek_int64() const {
    return util::ntoh64(*static_cast<uint64_t*>(
        reinterpret_cast<void*>(const_cast<char*>(peek(8).data()))));
}

std::string_view buffer::read() {
    return read(readable_bytes());
}

std::string_view buffer::read(size_t n) {
    auto res = peek(n);
    retrieve(n);
    return res;
}

uint8_t buffer::read_int8() {
    auto res = peek_int8();
    retrieve(1);
    return res;
}

uint16_t buffer::read_int16() {
    auto res = peek_int16();
    retrieve(2);
    return res;
}

uint32_t buffer::read_int32() {
    auto res = peek_int32();
    retrieve(4);
    return res;
}

uint64_t buffer::read_int64() {
    auto res = peek_int64();
    retrieve(8);
    return res;
}

int buffer::read_fd(int fd, int& err) {
    char ext_buff[1024 * 8];
    size_t wbs = writeable_bytes();
    struct iovec vec[2]{
        {begin() + tail_, wbs},
        {ext_buff, sizeof(ext_buff)},
    };
    int io_cnt = wbs < sizeof(ext_buff) ? 2 : 1;
    auto n = ::readv(fd, vec, io_cnt);
    if (n >= 0) {
        if (n < wbs) {
            tail_ += n;
        } else {
            tail_ = data_.size();
            append({ext_buff, n - wbs});
        }
    } else {
        err = errno;
    }
    return n;
}

size_t buffer::readed_bytes() const {
    return head_;
}

void buffer::ensure_writeable_bytes(size_t len) {
    if (writeable_bytes() >= len) {
        return;
    }
    if (readed_bytes() + writeable_bytes() >= len) {
        size_t tail = readable_bytes();
        std::copy(begin() + head_, begin() + tail_, begin());
        head_ = 0;
        tail_ = tail;
    } else {
        if (data_.size() * 3 / 2 <= tail_ + len) {
            data_.resize(tail_ + len);
        } else {
            data_.resize(data_.size() * 3 / 2);
        }
    }
}

void buffer::retrieve(size_t len) {
    if (len >= readable_bytes()) {
        retrieve_all();
        return;
    }
    head_ += len;
}

void buffer::retrieve_all() {
    head_ = tail_ = 0;
    data_.resize(init_length);
    data_.shrink_to_fit();
}

}  // namespace hestina
