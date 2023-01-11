#pragma once

#include <hestina/net/http_common.h>

#include <string>
#include <unordered_map>

namespace hestina {

class http_response {
public:
    http_response(version_t version, status_code_t code = status_code_t::kok);

    status_code_t code() const;
    void set_code(status_code_t code);

    const std::unordered_map<std::string, std::string>& headers() const;
    void add_header(const std::string& lhs, const std::string& rhs);

    std::string_view body() const;
    void set_body(std::string_view body);

    content_type_t content_type() const;
    void set_content_type(content_type_t type);

    std::string data() const;

private:
    version_t version_;
    status_code_t code_;

    std::unordered_map<std::string, std::string> headers_;
    std::string body_;
    content_type_t type_{content_type_t::ktext_plain};
};

}  // namespace hestina
