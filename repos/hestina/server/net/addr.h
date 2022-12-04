#pragma once

#include <string_view>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

namespace hestina {
class addr {
public:
    addr(std::string_view ip = "", uint16_t port = 0);

    static socklen_t len() { return sizeof(sockaddr_in); }
    const struct sockaddr* sockaddr() const;

private:
    sockaddr_in sockaddr_;
};
}  // namespace hestina
