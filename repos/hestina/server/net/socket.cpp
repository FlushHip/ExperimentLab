#include "socket.h"

#include "addr.h"

#include <fcntl.h>
#include <openssl/bio.h>
#include <sys/socket.h>

#include <cassert>
#include <cerrno>

namespace hestina {

socket::socket(int fd) : fd_(fd) {
    assert(fd != -1);
}

socket::socket() : socket(::socket(AF_INET, SOCK_STREAM, 0)) {}

socket::~socket() {
    if (fd_ != -1) {
        close(fd_);
    }
}

int socket::fd() const {
    return fd_;
}

int socket::last_error() {
    int value = 0, len = 0;
    int ret = getsockopt(
        fd_, SOL_SOCKET, SO_ERROR, &value, reinterpret_cast<socklen_t*>(&len));
    return ret == -1 ? errno : value;
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
    socklen_t size = 0;
    int fd =
        ::accept(fd_, const_cast<struct sockaddr*>(addr.sockaddr()), &size);
    assert(fd != -1);
    return fd;
}

int socket::read(int size) {
    return 0;
}

}  // namespace hestina
