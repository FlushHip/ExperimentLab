#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string_view>

namespace hestina {
class addr {
public:
    addr(sockaddr_in data);
    addr(std::string_view ip = "", uint16_t port = 0);
    ~addr();

    static socklen_t len() { return sizeof(sockaddr_in); }
    const struct sockaddr* sockaddr() const;

    std::string ip() const;
    uint16_t port() const;
    std::pair<std::string, uint16_t> point() const;

private:
    sockaddr_in sockaddr_{0};
};
}  // namespace hestina
