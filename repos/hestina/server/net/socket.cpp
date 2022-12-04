#include "socket.h"

#include "addr.h"

#include <asm-generic/socket.h>
#include <fcntl.h>
#include <sys/socket.h>

#include <cassert>

namespace hestina {

socket::socket(int fd) : fd_(fd) {
    assert(fd != -1);
}

socket::socket() : socket(::socket(AF_INET, SOCK_STREAM, 0)) {}

int socket::fd() const {
    return fd_;
}

void socket::nonblocking(bool f) {
    if (f) {
        fcntl(fd_, F_SETFL, fcntl(fd_, F_GETFL) | O_NONBLOCK);
    }
}

void socket::reuse_port(bool f) {
    int value = f ? 1 : 0;
    int ret = setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &value, sizeof(value));
    assert(ret != -1);
}

void socket::reuse_addr(bool f) {
    int value = f ? 1 : 0;
    int ret = setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
    assert(ret != -1);
}

void socket::bind(const addr& addr) {
    int ret = ::bind(fd_, addr.sockaddr(), addr::len());
    assert(ret == 0);
}

void socket::listen() {
    int ret = ::listen(fd_, SOMAXCONN);
    assert(ret == 0);
}

int socket::accept(addr& addr) {
    socklen_t size;
    int fd =
        ::accept(fd_, const_cast<struct sockaddr*>(addr.sockaddr()), &size);
    assert(fd != -1);
    return fd;
}

int socket::read(int size) {
    return 0;
}

}  // namespace hestina
