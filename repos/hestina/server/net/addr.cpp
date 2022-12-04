#include "addr.h"

#include <arpa/inet.h>
#include <sys/socket.h>

#include <cstring>

namespace hestina {

addr::addr(std::string_view ip, uint16_t port) {
    std::memset(&sockaddr_, 0, sizeof(sockaddr_));
    sockaddr_.sin_family = AF_INET;
    sockaddr_.sin_port = htons(port);
    sockaddr_.sin_addr.s_addr = inet_addr(ip.data());
}

const struct sockaddr* addr::sockaddr() const {
    return reinterpret_cast<const struct sockaddr*>(&sockaddr_);
}
}  // namespace hestina
