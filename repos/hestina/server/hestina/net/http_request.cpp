#include "http_request.h"

namespace hestina {

method_t http_request::method() const {
    return method_;
}

version_t http_request::version() const {
    return version_;
}

std::string_view http_request::path() const {
    return path_;
}

std::string_view http_request::params() const {
    return params_;
}

const std::unordered_map<std::string, std::string>& http_request::headers()
    const {
    return headers_;
}

}  // namespace hestina
