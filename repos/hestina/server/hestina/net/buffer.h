#pragma once

#include <string>

namespace hestina {

class buffer {
public:
    enum { init_length = 1024 };
    buffer(size_t length = init_length);
    int read_fd(int fd, int& err);
    void append(std::string_view data);
    size_t readable_bytes() const;
    size_t writeable_bytes() const;

    std::string_view peek() const;
    std::string_view peek(size_t n) const;
    uint8_t peek_int8() const;
    uint16_t peek_int16() const;
    uint32_t peek_int32() const;
    uint64_t peek_int64() const;

    std::string_view read();
    std::string_view read(size_t n);
    uint8_t read_int8();
    uint16_t read_int16();
    uint32_t read_int32();
    uint64_t read_int64();

    std::string_view data();

    void retrieve(size_t len);
    void retrieve_all();

    void clear();

private:
    char* begin();
    const char* begin() const;
    size_t readed_bytes() const;
    void ensure_writeable_bytes(size_t len);

    size_t head_{0};
    size_t tail_{0};
    std::string data_;
};

}  // namespace hestina
