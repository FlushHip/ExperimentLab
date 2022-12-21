#include "socket.h"

#include "addr.h"

#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

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

int socket::connect(const addr& addr) {
    int ret = ::connect(fd_, addr.sockaddr(), addr.len());
    assert(ret == 0 ||
        (errno == EINPROGRESS || errno == EINTR || errno == EISCONN));
    return ret;
}

int socket::read(char* buff, int size) {
    return ::read(fd_, buff, size);
}

int socket::write(const char* buff, int size) {
    return ::write(fd_, buff, size);
}

std::unique_ptr<addr> socket::local_addr() {
    struct sockaddr_in address {};
    socklen_t len{static_cast<socklen_t>(sizeof(address))};

    int ret =
        getsockname(fd_, static_cast<struct sockaddr*>((void*)&address), &len);
    assert(ret == 0);
    return std::make_unique<addr>(address);
}

std::unique_ptr<addr> socket::peer_addr() {
    struct sockaddr_in address {};
    socklen_t len{static_cast<socklen_t>(sizeof(address))};

    int ret =
        getpeername(fd_, static_cast<struct sockaddr*>((void*)&address), &len);
    if (ret != 0) {
        return nullptr;
    }
    return std::make_unique<addr>(address);
}

}  // namespace hestina
