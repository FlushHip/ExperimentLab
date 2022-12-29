#pragma once

#include <hestina/net/http_request.h>

namespace hestina {

class buffer;

class http_parser {
public:
    http_parser();
    ~http_parser();

    bool parse_request(buffer* buff);
    const http_request& request() const;

private:
    enum class parse_status {
        kmethod,
        kpath,
        kversion,
        kheaders,
        kbody,
        kend,
    };

    http_request request_;
    parse_status status_{parse_status::kmethod};
};

}  // namespace hestina
