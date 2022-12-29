#pragma once

#include <hestina/net/http_common.h>

#include <string>
#include <unordered_map>

namespace hestina {

class http_parser;

class http_request {
public:
    method_t method() const;
    version_t version() const;
    std::string_view path() const;
    std::string_view params() const;
    const std::unordered_map<std::string, std::string>& headers() const;

private:
    friend class http_parser;

    method_t method_;
    version_t version_;
    std::string path_;
    std::string params_;
    std::unordered_map<std::string, std::string> headers_;
};

}  // namespace hestina
