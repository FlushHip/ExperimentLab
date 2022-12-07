#include "addr.h"

#include <arpa/inet.h>
#include <sys/socket.h>

#include <cstring>
#include <string>

namespace hestina {

addr::addr(sockaddr_in data) : sockaddr_(data) {}

addr::addr(std::string_view ip, uint16_t port) {
    std::memset(&sockaddr_, 0, sizeof(sockaddr_));
    sockaddr_.sin_family = AF_INET;
    sockaddr_.sin_port = htons(port);
    sockaddr_.sin_addr.s_addr = inet_addr(ip.data());
}

addr::~addr() = default;

const struct sockaddr* addr::sockaddr() const {
    return reinterpret_cast<const struct sockaddr*>(&sockaddr_);
}

std::string addr::ip() const {
    char buf[64] = {0};
    ::inet_ntop(AF_INET, &sockaddr_.sin_addr, buf, sizeof(buf));
    return buf;
}

uint16_t addr::port() const {
    return ntohs(sockaddr_.sin_port);
}

std::pair<std::string, uint16_t> addr::point() const {
    return {ip(), port()};
}

}  // namespace hestina
