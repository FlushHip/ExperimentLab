#pragma once

#include <memory>
#include <string_view>
namespace hestina {
class addr;
class socket {
public:
    socket();
    socket(int fd);
    ~socket();

    int fd() const;
    int last_error();

    void nonblocking(bool f = true);
    void reuse_port(bool f = true);
    void reuse_addr(bool f = true);

    void bind(const addr& addr);
    void listen();
    int accept(addr& addr);

    int read(char* buff, int size);
    int write(const char* buff, int size);

    std::unique_ptr<addr> local_addr();
    std::unique_ptr<addr> peer_addr();

private:
    int fd_;
};
}  // namespace hestina
