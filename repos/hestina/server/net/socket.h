#pragma once

namespace hestina {
class addr;
class socket {
public:
    socket();
    socket(int fd);
    ~socket();

    int fd() const;

    void nonblocking(bool f = true);
    void reuse_port(bool f = true);
    void reuse_addr(bool f = true);

    void bind(const addr& addr);
    void listen();
    int accept(addr& addr);

    int read(int size);

private:
    int fd_;
};
}  // namespace hestina
